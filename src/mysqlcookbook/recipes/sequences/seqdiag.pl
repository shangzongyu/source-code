#!/usr/bin/perl
# seqdiag.pl: test AUTO_INCREMENT operations

# If server version precedes introduction of SHOW CREATE, indicate that we
# cannot tell whether the table was created properly.  Or just catch the
# error; then don't need server version.

use strict;
use warnings;
use DBI;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "seqdiag.pl";
my $usage = <<EOF;
Usage: $prog [options] [db_name [tbl_name [tbl_engine]]]

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
    Specify MySQL socket pathname
--user=user_name, -u user_name
    Specify MySQL username

db_name
    Specify database name to use (default test)
tbl_name
    Specify table name to use (default t)
tbl_engine
    Specify table engine to use (default InnoDB)
EOF

# Variables for command line options; most are undefined initially.
my $help;
my ($host_name, $password, $port_num, $socket_name, $user_name);

GetOptions (
  # =i means an integer value is required after the option
  # =s means a string value is required after the option
  "help"          => \$help,        # print help message
  "host|h=s"      => \$host_name,   # server host
  "password|p=s"  => \$password,    # password
  "port|P=i"      => \$port_num,    # port number
  "socket|S=s"    => \$socket_name, # socket name
  "user|u=s"      => \$user_name    # username
) or die "$usage\n";

die "$usage\n" if defined ($help);

@ARGV <= 3 or die "$usage\n";

my ($db_name, $tbl_name, $tbl_engine) = ("test", "t", "InnoDB");
$db_name = shift (@ARGV) if @ARGV;
$tbl_name = shift (@ARGV) if @ARGV;
$tbl_engine = shift (@ARGV) if @ARGV;

$tbl_engine =~ /^[a-z0-9_]+$/i    # letters, digits, underscore permitted
  or die "Suspicious table engine given: $tbl_engine\n";

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

my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, $user_name, $password, $conn_attrs);

$db_name = $dbh->quote_identifier ($db_name);
$tbl_name = $dbh->quote_identifier ($tbl_name);

my ($ver_str, $ver_num) = get_server_version ($dbh);
printf "Server version: %s\n", $ver_str if defined ($ver_str);
printf "Using database: %s\n", $db_name;
printf "Using table: %s\n", $tbl_name;
printf "Using table engine: %s\n", $tbl_engine;

my $seq;
my $seq2;

# Normally, you insert NULL to generate a new AUTO_INCREMENT value.
# Check whether inserting 0 is same as inserting NULL.

print "Check whether inserting 0 is same as inserting NULL\n";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 3);
$seq = get_seq_val ($dbh);
print "  Sequence value after inserting NULL three times: $seq\n";
gen_seq_val_with_zero ($dbh, $tbl_name, 3);
$seq = get_seq_val ($dbh);
print "  Sequence value after inserting zero three times: $seq\n";

# See what happens when updating an AUTO_INCREMENT column to NULL
# (expected behavior: you get a new sequence value), or to 0
# (expected behavior: varies!).
# Have to retrieve updated value using MAX(), because UPDATE doesn't
# set LAST_INSERT_ID().

print "Check effect of updating existing AUTO_INCREMENT value\n";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 1);
$seq = get_seq_val ($dbh);
$dbh->do ("UPDATE $tbl_name SET seq = 0 where seq = ?", undef, $seq);
$seq2 = $dbh->selectrow_array ("SELECT MAX(seq) FROM $tbl_name");
print "  Sequence value before/after updating to 0: $seq/$seq2\n";
display_table ($dbh, $tbl_name);

# See what happens after updating an AUTO_INCREMENT column to a value
# larger than any sequence number.  Does sequence continue from that point?

print "Check effect of updating existing AUTO_INCREMENT value\n";
print "and then generating new AUTO_INCREMENT value\n";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 3);
$seq = get_seq_val ($dbh);
$dbh->do ("UPDATE $tbl_name SET seq = 1000 where seq = ?", undef, $seq);
gen_seq_val ($dbh, $tbl_name, 1);
$seq = get_seq_val ($dbh);
print "  Next sequence value after updating 3 to 1000: $seq\n";

# - create table
# - insert three records
# - delete row at top of sequence
# - insert another record, see whether top value was reused

print "Is a value deleted from top of sequence reused?";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 3);
$seq = get_seq_val ($dbh);
$dbh->do ("DELETE FROM $tbl_name WHERE seq = ?", undef, $seq);
gen_seq_val ($dbh, $tbl_name, 1);
printf " %s\n", ($seq == get_seq_val ($dbh) ? "yes" : "no");

# - create table
# - insert three records
# - delete rows one at a time
# - insert another record, see whether sequence was reset to 1

print "Does deleting rows one at a time reset the sequence?";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 3);
$dbh->do ("DELETE FROM $tbl_name WHERE 1");
gen_seq_val ($dbh, $tbl_name, 1);
$seq = get_seq_val ($dbh);
printf " %s\n", ($seq == 1 ? "yes" : "no");

# - create table
# - insert three records
# - delete rows all at one with DELETE
# - insert another record, see whether sequence was reset to 1

print "Does deleting rows all at once with DELETE reset the sequence?";
init_table ($dbh, $tbl_name, $tbl_engine);
gen_seq_val ($dbh, $tbl_name, 3);
$dbh->do ("DELETE FROM $tbl_name");
gen_seq_val ($dbh, $tbl_name, 1);
$seq = get_seq_val ($dbh);
printf " %s\n", ($seq == 1 ? "yes" : "no");

# - create table
# - insert three records
# - delete rows all at one with TRUNCATE
# - insert another record, see whether sequence was reset to 1

#### This should check whether TRUNCATE is available!  And if it is, it
#### should use version to determine whether TABLE must be omitted

print "Does deleting rows all at once with TRUNCATE reset the sequence?";
if ($ver_num < 32328)
{
  print "\n  (test skipped, TRUNCATE not available prior to 3.23.28)\n";
}
else
{
  init_table ($dbh, $tbl_name, $tbl_engine);
  gen_seq_val ($dbh, $tbl_name, 3);
  if ($ver_num < 32333) # must omit "TABLE"
  {
    $dbh->do ("TRUNCATE $tbl_name");
  }
  else
  {
    $dbh->do ("TRUNCATE TABLE $tbl_name");
  }
  gen_seq_val ($dbh, $tbl_name, 1);
  $seq = get_seq_val ($dbh);
  printf " %s\n", ($seq == 1 ? "yes" : "no");
}

#$dbh->do ("DROP TABLE IF EXISTS $tbl_name");
$dbh->disconnect ();

# ----------------------------------------------------------------------

# Given a database handle, drop and recreate the $tbl_name table.

sub init_table
{
my ($dbh, $tbl_name, $tbl_engine) = @_;

  my $stmt = "CREATE TABLE $tbl_name
        (seq INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (seq))";
  my $ver_num = (get_server_version ($dbh))[1];
  if ($ver_num >= 32300)
  {
    $stmt .= " ENGINE=$tbl_engine";
  }
  elsif (uc ($tbl_engine) ne "ISAM")
  {
    die "Table engine must be ISAM for MySQL < 3.23.00\n";
  }
  $dbh->do ("DROP TABLE IF EXISTS $tbl_name");
  $dbh->do ($stmt);
  # if SHOW CREATE TABLE is not available (3.23.20), have to assume
  # that table was created correctly
  return if $ver_num < 32320;
  my ($junk, $str) = $dbh->selectrow_array ("SHOW CREATE TABLE $tbl_name");
  if ($str =~ /\)\s*ENGINE=(\S*)/)
  {
    my $new_tbl_engine = $1;
    #print "$tbl_engine = $new_tbl_engine?\n";
    return if lc ($tbl_engine) eq lc ($new_tbl_engine);
  }
  print "FATAL ERROR: ";
  print "Table $tbl_name was not created with requested engine $tbl_engine\n";
  print "(perhaps the server does not support that table engine)\n";
  exit (1);
}

# Given a database handle and a count, generate some AUTO_INCREMENT values.
# The count defaults to 1 if not specified

sub gen_seq_val
{
my ($dbh, $tbl_name, $count) = @_;

  $count = 1 unless defined ($count);

  for (1 .. $count)
  {
    $dbh->do (qq{
        INSERT INTO $tbl_name (seq)
        VALUES(NULL)
      });
  }
}

# Like gen_seq_val(), but inserts 0 rather than NULL (can be used to
# see if that's equivalent to inserting NULL)

sub gen_seq_val_with_zero
{
my ($dbh, $tbl_name, $count) = @_;

  $count = 1 unless defined ($count);

  for (1 .. $count)
  {
    $dbh->do (qq{
        INSERT INTO $tbl_name (seq)
        VALUES(0)
      });
  }
}

sub get_seq_val
{
my $dbh = shift;

  return ($dbh->selectrow_array ("SELECT LAST_INSERT_ID()"));
}

sub display_table
{
my ($dbh, $tbl_name) = @_;

  my $ref = $dbh->selectall_arrayref ("SELECT * FROM $tbl_name");
  if (!$ref)
  {
    print "  cannot display table $tbl_name\n";
  }
  else
  {
    foreach my $row_ref (@{$ref})
    {
      print "  " . join (",", @{$row_ref}) . "\n";
    }
  }
}

# Return a list consisting of the server version number in both string
# and numeric forms.  Return undef on an error.

sub get_server_version
{
my $dbh = shift;
my ($ver_str, $ver_num);
my ($major, $minor, $patch);

  # fetch result into scalar string
  $ver_str = $dbh->selectrow_array ("SELECT VERSION()");
  return undef unless defined ($ver_str);
  ($major, $minor, $patch) = split (/\./, $ver_str);
  $patch =~ s/\D.*$//; # strip any nonnumeric suffix if present
  $ver_num = $major*10000 + $minor*100 + $patch;
  return ($ver_str, $ver_num);
}
