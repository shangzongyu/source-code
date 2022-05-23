#!/usr/bin/perl
#@ _INTRO_
# mysql_to_text.pl: Export MySQL query output in user-specified text format.

# Usage: mysql_to_text.pl [ options ] [db_name] > text_file
#@ _INTRO_

# Paul DuBois
# paul@kitebird.com
# 2002-01-29

#@ _SETUP_1_
use strict;
use warnings;
use DBI;
use Text::CSV_XS;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled
#@ _SETUP_1_

# ----------------------------------------------------------------------

#@ _INTERPRET_OPTION_
# Interpret a string that may contain special sequences:
# 0xhh, 0Xhh - char specified as hex value
# \n, \r, \t, \0, \\ - tab, linefeed, carriage return, NUL backslash

sub interpret_option
{
my $s_in = shift;
my $s_out;
my %escmap = (      # map escape sequences to characters
  "n"   => "\n",
  "r"   => "\r",
  "t"   => "\t",
  "0"   => "\0",
  "\\"  => "\\"
);

  return undef unless defined ($s_in);
  while ($s_in ne "")
  {
    if ($s_in =~ /^0x/i)          # hex value
    {
      $s_out .= pack ("H2", substr ($s_in, 2, 2));
      $s_in = substr ($s_in, 4);
    }
    elsif (substr ($s_in, 0, 1) eq "\\")  # escape sequence
    {
      my $c = substr ($s_in, 1, 1);
      # use char mapping, or char itself if not in map
      $s_out .= (exists ($escmap{$c}) ? $escmap{$c} : $c);
      $s_in = substr ($s_in, 2);
    }
    else                  # literal char
    {
      $s_out .= substr ($s_in, 0, 1);
      $s_in = substr ($s_in, 1);
    }
  }
  return $s_out;
}
#@ _INTERPRET_OPTION_

# ----------------------------------------------------------------------

my $prog = "mysql_to_text.pl";

my $usage = <<EOF;
Usage: $prog [options]

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
--execute=query, -equery
    Specify query to execute
--table=tbl_name, -t tbl_name
    Specify table to export
--labels, -l
    Generate initial row of column labels
--delim=c
    Specify column delimiter (default: tab)
--quote=c
    Specify column delimiter (default: no quotes)
--eol=c
    Specify end-of-line sequence (default: linefeed)
EOF

#@ _SETUP_2_
# Variables for command line options - all undefined initially
# except for options that control output structure, which is set
# to be tab-delimited, linefeed-terminated.
my $help;
my ($host_name, $password, $port_num, $socket_name, $user_name, $db_name);
my ($stmt, $tbl_name);
my $labels;
my $delim = "\t";
my $quote;
my $eol = "\n";

GetOptions (
  # =i means an integer value is required after the option
  # =s means a string value is required after the option
  "help"          => \$help,        # print help message
  "host|h=s"      => \$host_name,   # server host
  "password|p=s"  => \$password,    # password
  "port|P=i"      => \$port_num,    # port number
  "socket|S=s"    => \$socket_name, # socket name
  "user|u=s"      => \$user_name,   # username
  "execute|e=s"   => \$stmt,        # statement to execute
  "table|t=s"     => \$tbl_name,    # table to export
  "labels|l"      => \$labels,      # generate row of column labels
  "delim=s"       => \$delim,       # column delimiter
  "quote=s"       => \$quote,       # column quoting character
  "eol=s"         => \$eol          # end-of-line (record) delimiter
) or die "$usage\n";

die "$usage\n" if defined ($help);

$db_name = shift (@ARGV) if @ARGV;

# One of --execute or --table must be specified, but not both
die "You must specify a query or a table name\n\n$usage\n"
  unless defined ($stmt) || defined ($tbl_name);
die "You cannot specify both a query and a table name\n\n$usage\n"
  if defined ($stmt) && defined ($tbl_name);

# interpret special chars in the file structure options
$quote = interpret_option ($quote);
$delim = interpret_option ($delim);
$eol = interpret_option ($eol);
#@ _SETUP_2_

# Construct data source name and connect to the server.  The database
# name comes from the command line.  Client connection parameters can
# come from one of the standard option files or from the command line.

#@ _CONNECT_
my $dsn = "DBI:mysql:";
$dsn .= ";database=$db_name" if $db_name;
$dsn .= ";host=$host_name" if $host_name;
$dsn .= ";port=$port_num" if $port_num;
$dsn .= ";mysql_socket=$socket_name" if $socket_name;
# read [client] group parameters from standard option files
$dsn .= ";mysql_read_default_group=client";

my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, $user_name, $password, $conn_attrs);
#@ _CONNECT_

# By specifying the eol sequence here, $csv will it add it to output
# lines automatically.
#@ _CREATE_CSV_
my $csv = Text::CSV_XS->new ({
  sep_char    => $delim,
  quote_char  => $quote,
  escape_char => $quote,
  eol         => $eol,
  binary      => 1
});
#@ _CREATE_CSV_

# Run query to dump all data contained in the table, preceded by a row of
# column labels if the --labels option was given.  (Labels are available
# in the array pointed to by $sth->{NAME} after calling execute().)

#@ _EXECUTE_AND_PRINT_COLUMN_NAMES_
# If table name was given, use it to create query that selects entire table.
# Split on dots in case it's a qualified name, to quote parts separately.
$stmt = "SELECT * FROM " . $dbh->quote_identifier (split (/\./, $tbl_name))
  if defined ($tbl_name);

warn "$stmt\n";
my $sth = $dbh->prepare ($stmt);
$sth->execute ();
if ($labels)                # write row of column labels
{
  $csv->combine (@{$sth->{NAME}}) or die "cannot process column labels\n";
  print $csv->string ();
}
#@ _EXECUTE_AND_PRINT_COLUMN_NAMES_
#@ _EXTRACT_
my $count = 0;
while (my @val = $sth->fetchrow_array ())
{
  ++$count;
  $csv->combine (@val) or die "cannot process column values, row $count\n";
  print $csv->string ();
}
#@ _EXTRACT_

$dbh->disconnect ();
