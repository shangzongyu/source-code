#!/usr/bin/perl
# load_diag.pl: LOAD DATA diagnostic.

# Simulates the effect of running a LOAD DATA statement, but attempts
# to determine which rows and columns result in warnings or errors.

# Usage: load_diag.pl [options] db_name tbl_name data_file

# Paul DuBois
# paul@kitebird.com
# 2002-02-14

# 2002-02-14
# - Created.
# 2002-02-20
# - Add --labels option to indicate first data row contains labels and
#   should be skipped.
# - Create scratch table using information from SHOW COLUMNS rather than
#   from SHOW CREATE TABLE.  This means MySQL 3.23.19 or higher is no longer
#   required, and also doesn't create any indexes in the scratch table,
#   which can make the initial load of the entire data file run much more
#   quickly. (Consider if the file is large and has a FULLTEXT index, for
#   example.)  On the other hand, "duplicate key" errors no longer can be
#   flagged.
# 2002-02-21
# - Add --skip-full-load option to skip initial test that loads the entire
#   file.
# - Try several directories to find one that works for creating the
#   temp file.
# 2002-03-01
# - Minor changes to report format
# 2002-03-04
# - Added --help option.
# 2002-03-29
# - Fix bug in the CREATE TABLE statement generation; was adding DEFAULT
#   NULL for AUTO_INCREMENT and TIMESTAMP columns, which can't contain NULL.
# 2002-06-27
# - Fix bug in use of $ENV{TEMP} and $ENV{TMP} on Windows.
# 2002-07-16
# - Report stats for missing column values.
# 2002-07-26
# - Query the server for its version number and use it to determine
#   availability of temporary tables and quoted identifiers (like `xyz`).
# 2002-09-15
# - Added --port, --socket options.
# 2003-04-30
# - Reference DBD::mysql module explicitly so that we can check the value
#   of $DBD::mysql::VERSION.  Use it to determine whether the connection
#   option mysql_local_infile can be used, and enable it if it can.

use strict;
use warnings;
use DBI;
use DBD::mysql;   # reference explicitly so we can access version
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "load_diag.pl";
my $usage = <<EOF;
Usage: $prog [options] db_name tbl_name data_file

Options:
--help
    Print this message
--host=host_name, -h host_name
    Specify MySQL server host
--password=pass_val, -ppass_val
    Specify MySQL password
--port=port_num, -P port_num
    Specify MySQL TCP/IP port number
--socket=socket_name, -S socket_name
    Specify MySQL socket file pathname
--user=user_name, -u user_name
    Specify MySQL username
--columns=name1,name2,name3,...
    Indicate which table columns the data file contains
--labels, -l
    Skip first row of data file, it contains column labels
--skip-full-load
    Skip initial full-file load test
--tmp-table=tbl_name
    Specify temporary table name (default = _load_diag_<process_id>).
    This table must not already exist.

Required arguments:
db_name, tbl_name
    Name of database and table you'll eventually load the
    data file into
data_file
    Name of data file to check
EOF

# Pathname component separator, candidates for temporary file directory,
# and temporary file name

my $path_sep = "/";
my @tmp_dir = ( "/tmp", "/var/tmp", "/usr/tmp" );
unshift (@tmp_dir, $ENV{TMPDIR}) if exists ($ENV{TMPDIR});
my $tmp_file;

# Reset pathname separator and candidate directory list for Windows/DOS

if ($^O =~ /^MSWin/i || $^O =~ /^dos/)
{
  $path_sep = "\\";
  @tmp_dir =  ( "C:\\Temp", "C:\\WinNT\\Temp", "C:\\Windows\\Temp" );
  unshift (@tmp_dir, $ENV{TMP}) if exists ($ENV{TMP});
  unshift (@tmp_dir, $ENV{TEMP}) if exists ($ENV{TEMP});
}

# Construct temp file name and make sure we can write to it.
# Use the first directory in @tmp_dir that works.

foreach my $dir (@tmp_dir)
{
  my $file = $dir . $path_sep . "load_diag." . $$;
  if (open (OUT, ">$file"))
  {
    close (OUT);
    unlink ($file);
    $tmp_file = $file;
    last;
  }
}

die "Cannot find directory in which to create temp file\n"
    . "(tried: @tmp_dir)\n"
  unless defined ($tmp_file);

# Variables for command line options; most are undefined initially.
my $help;
my ($host_name, $password, $port_num, $socket_name, $user_name);
my $tmp_tbl_name = "_load_diag_$$";
my $labels;
my $skip_full;
my $columns;

GetOptions (
  # =i means an integer value is required after the option
  # =s means a string value is required after the option
  "help"           => \$help,        # print help message
  "host|h=s"       => \$host_name,   # server host
  "password|p=s"   => \$password,    # password
  "port|P=i"       => \$port_num,    # port number
  "socket|S=s"     => \$socket_name, # socket name
  "user|u=s"       => \$user_name,   # username
  "columns=s"      => \$columns,     # column list
  "labels|l"       => \$labels,      # first row contains column labels
  "skip-full-load" => \$skip_full,   # skip full load test
  "tmp-table|t=s"  => \$tmp_tbl_name # name to use for temporary table
) or die "$usage\n";

die "$usage\n" if defined ($help);

@ARGV == 3 or die "$usage\n";

my $db_name = shift (@ARGV);
my $tbl_name = shift (@ARGV);
my $file_name = shift (@ARGV);

-r $file_name or die "$file_name does not exist or is unreadable\n";

$labels = defined ($labels);  # convert defined/undefined to boolean
$skip_full = defined ($skip_full);

# List of columns in data file.  Default = all columns; may be overridden
# with --columns option.

my @col_list;
if (defined ($columns))
{
  @col_list = split (/,/, $columns) if defined ($columns);
  @col_list or die "$usage\n";      # column list was empty
}

# Construct data source name and connect to the server.  The database
# name comes from the command line.  Client connection parameters can
# come from one of the standard option files or from the command line.

my $dsn = "DBI:mysql:";
$dsn .= ";database=$db_name" if $db_name;
$dsn .= ";host=$host_name" if $host_name;
$dsn .= ";port=$port_num" if $port_num;
$dsn .= ";mysql_socket=$socket_name" if $socket_name;
# read [client] group parameters from standard option files
$dsn .= ";mysql_read_default_group=client";
# enable local infile option if DBD::mysql is recent enough to support it
$dsn .= ";mysql_local_infile=1" if $DBD::mysql::VERSION >= 2.1020;;

my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, $user_name, $password, $conn_attrs);

# Get server version number for use in determining whether temporary
# tables are available (3.23.2) and whether quoted identifiers are
# available (3.23.6)

my $ver_num = get_server_version_number ($dbh); # server version, numeric
my $quote = ($ver_num >= 32306 ? "`" : "");

# Check whether the scratch table already exists.  If so, be
# conservative and just warn the user and exit.  (The SHOW TABLES
# statement will return > 0 rows if the table exists.)

my $s = $tmp_tbl_name;
$s =~ s/([%_])/\\$1/g;  # escape any special characters
if ($dbh->selectrow_array ("SHOW TABLES FROM $quote$db_name$quote LIKE '$s'"))
{
  warn "WARNING: the $tmp_tbl_name table already exists!\n";
  warn "If you really want to use it for $prog, drop it manually\n";
  warn "and run $prog again.\n";
  exit (1);
}

# Read SHOW COLUMNS information for the table

my $tbl_info = $dbh->selectall_arrayref (
            "SHOW COLUMNS FROM $quote$tbl_name$quote");

# Determine which columns to create in the temporary table.
# If @col_list is nonempty, the --columns argument was given
# and indicates which columns the data file contains.  If @col_list
# is empty, assume the data file contains a column for every table
# column.

if (!@col_list)             # use all columns in the table
{
  foreach my $ref (@{$tbl_info})
  {
    push (@col_list, $ref->[0]);
  }
}

# Generate a CREATE TABLE statement for the temporary table.
# Set up an information structure for each of its columns.
# Determine the length of the longest column name (needed for report
# at the end).

my @col_info;
my $max_col_name_len = 0;
my $stmt = "";

foreach my $name (@col_list)
{
  my $info;
  my ($type, $nullable, $key, $default, $extra);

  # Find the row of SHOW COLUMNS information for this column

  foreach my $row_ref (@{$tbl_info})
  {
    # use case-insensitive comparison
    if (lc ($name) eq lc ($row_ref->[0]))
    {
      $info = {};
      ($name, $type, $nullable, $key, $default, $extra) = @{$row_ref};
      last;
    }
  }
  # Did user name a bad column in --columns?
  die "$name is not a column in $tbl_name\n" unless defined ($info);
      
  # Set up info hash for keeping track of load status for the column

  $info->{name} = $name;      # column name;
  $info->{missing_count} = 0;   # number of times column was missing
  $info->{warn_count} = 0;    # per-column warning count
  $info->{empty_warn_count} = 0;  # number of warnings for empty columns
  $info->{null_ok_count} = 0;   # number of warnings that go away
                  # by loading NULL rather than ""
  push (@col_info, $info);

  $max_col_name_len = length ($name) if $max_col_name_len < length ($name);

  # Generate column definition for CREATE TABLE statement

  $nullable = ($nullable eq "YES" ? "NULL" : "NOT NULL");
  # add DEFAULT clause except for TIMESTAMP and AUTO_INCREMENT columns
  if ($type =~ /^timestamp/ || $extra eq "auto_increment")
  {
    $default = "";
  }
  else
  {
    $default = "DEFAULT " . $dbh->quote ($default);
  }
  $stmt .= ",\n" if $stmt ne "";
  $stmt .= "\t$quote$name$quote $type $nullable $default";
}

# Complete the table-creation statement for the scratch table, and
# then execute it.  If true temporary tables are available, use one.

if ($ver_num >= 32302)
{
  $stmt = "CREATE TEMPORARY TABLE $quote$tmp_tbl_name$quote\n(\n$stmt\n)\n";
}
else
{
  $stmt = "CREATE TABLE $quote$tmp_tbl_name$quote\n(\n$stmt\n)\n";
}
$dbh->do ($stmt);

# Load entire data file, see if it loads correctly.  Skip initial line if
# --labels was specified.  Skip the entire test if --skip-full-load was
# specified.

my $file_warnings = 0;

if (!$skip_full)
{
  $file_warnings = test_load ($dbh, $file_name, $quote, $tmp_tbl_name, undef,
                  ($labels ? 1 : undef));
  if ($file_warnings == 0)
  {
    print "File loaded with no warnings, no per-record tests performed\n";
    # Dump scratch table
    $dbh->do ("DROP TABLE IF EXISTS $quote$tmp_tbl_name$quote");
    $dbh->disconnect ();
    exit (0);
  }
  $dbh->do ("DELETE FROM $quote$tmp_tbl_name$quote"); # clear the table
}

my $excess_columns = 0;
my $too_few_columns = 0;

# Read data file, try loading it line by line

open (IN, $file_name) or die "Cannot read data file $file_name: $!\n";
<IN> if $labels;          # skip first line
while (defined (my $line = <IN>))
{
  # save line's fields for later, in case there's a problem
  chomp ($line);
  my @val = split (/\t/, $line, 10000); # split, preserving all fields

  # Load entire line first
  write_tmp_file ($tmp_file, $line);
  my $line_warnings = test_load ($dbh, $tmp_file, $quote, $tmp_tbl_name);
  next if $line_warnings == 0;      # no problems

  # something went wrong; load individual columns and check the result

  printf "line $.: %d warning%s\n",
         $line_warnings, ($line_warnings == 1 ? "" : "s");
  if (@val > @col_info)     # extra columns in line
  {
    print "  excess number of columns\n";
    ++$excess_columns;
  }
  if (@val < @col_info)     # too few columns in line
  {
    print "  too few columns\n";
    ++$too_few_columns;
  }
  for my $i (0 .. @col_info - 1)
  {
    my $name = $col_info[$i]->{name};
    if ($i > @val - 1)    # was there even a column in the data line?
    {
      ++$col_info[$i]->{missing_count};
      printf "  column %d (%s): missing from input line\n", $i+1, $name;
      #next;
      $val[$i] = "";  # treat as an empty value for further tests
    }
    write_tmp_file ($tmp_file, $val[$i]);
    my $col_warnings = test_load ($dbh, $tmp_file, $quote, $tmp_tbl_name,
                    $name);
    next if $col_warnings == 0;     # no problems
    ++$col_info[$i]->{warn_count};
    printf "  column %d (%s): bad value = (%s)", $i+1, $name, $val[$i];

    # if value is empty, try inserting NULL (\N) instead to see if
    # that works better
    if ($val[$i] eq "")
    {
      ++$col_info[$i]->{empty_warn_count};
      write_tmp_file ($tmp_file, "\\N");
      $col_warnings = test_load ($dbh, $tmp_file, $quote, $tmp_tbl_name,
                    $name);
      if ($col_warnings == 0)   # \N worked better
      {
        ++$col_info[$i]->{null_ok_count};
        printf " (inserting NULL worked better)";
      }
    }
    print "\n";
  }
}

my $line_count = $.;  # save this value; it disappears after close()
close (IN);

# Dump temp file and scratch table

unlink ($tmp_file);
$dbh->do ("DROP TABLE IF EXISTS $quote$tmp_tbl_name$quote");

$dbh->disconnect ();

# Print summary

print "\nNumber of lines in file: $line_count\n";
print "Warnings found when loading entire file: "
      . ($skip_full ? "(test not performed)" : $file_warnings)
      . "\n";
print "Lines containing too few column values: $too_few_columns\n";
print "Lines containing excess column values: $excess_columns\n";

print "\nWarnings per column:\n\n";
$max_col_name_len = 6 if $max_col_name_len < 6;
printf "%-*s   %-8s   %-8s   %-14s   %s\n",
       $max_col_name_len,
       "Column",
       " Times",
       " Total",
       "Warnings for",
       "Improved";
printf "%-*s   %-8s   %-8s   %-14s   %s\n",
       $max_col_name_len,
       "",
       "missing",
       "warnings",
       "empty columns",
       "with NULL";
for my $i (0 .. @col_info - 1)
{
  printf "%-*s  %8d    %8d        %8d     %8d\n",
         $max_col_name_len,
         $col_info[$i]->{name},
         $col_info[$i]->{missing_count},
         $col_info[$i]->{warn_count},
         $col_info[$i]->{empty_warn_count},
         $col_info[$i]->{null_ok_count};
}

# ----------------------------------------------------------------------

# Write a data line or column value to a temporary file

sub write_tmp_file
{
my ($file_name, $data) = @_;

  open (OUT, ">$file_name") or die "Cannot open temp file $file_name: $!\n";
  print OUT "$data\n";
  close (OUT);
}

# Try loading some data contained in $file_name into the scratch table
# $tbl_name.  if $col_name is undef, assume the file contains an entire
# row of data.  Otherwise, assume that it represents a single column value.
# If $ignore is not undef, it indicate the number of initial lines to
# skip (used for full-file load test).  $quote is the quote character
# for identifiers (either ` or the empty string).

sub test_load
{
my ($dbh, $file_name, $quote, $tbl_name, $col_name, $ignore) = @_;

  # If filename contains backslashes, assume a Windows platform
  # and double the backslashes.

  $file_name =~ s/\\/\\\\/g;

  my $stmt=
    "LOAD DATA LOCAL INFILE '$file_name' INTO TABLE $quote$tbl_name$quote";
  # add column name for single-column test
  $stmt .= " ($quote$col_name$quote)" if defined ($col_name);
  $stmt .= " IGNORE $ignore LINES" if defined ($ignore);
  $dbh->do ($stmt);
  my $info = $dbh->{mysql_info};
  # use old form if new form unavailable
  $info = $dbh->{info} unless defined ($info);
  # extract and return warning count
  die "Cannot interpret info string:\n$info\n" if $info !~ /(\d+)$/;
  return $1;
}

# Get the server version in numeric form; return 0 if cannot get

sub get_server_version_number
{
my $dbh = shift;
my ($ver_str, $ver_num);
my ($major, $minor, $patch);

  # fetch result into scalar string
  $ver_str = $dbh->selectrow_array ("SELECT VERSION()");
  return 0 unless defined ($ver_str);
  ($major, $minor, $patch) = split (/\./, $ver_str);
  $patch =~ s/\D.*$//; # strip any nonnumeric suffix if present
  $ver_num = $major*10000 + $minor*100 + $patch;
  return $ver_num;
}
