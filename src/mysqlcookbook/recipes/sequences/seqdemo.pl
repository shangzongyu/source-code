#!/usr/bin/perl
# seqdemo.pl: demonstrate AUTO_INCREMENT operations

use strict;
use warnings;
use DBI;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "seqdemo.pl";
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
my $sth;
my $sth2;

# Make sure the table exists, dropping it first in case it already existed.

init_table ($dbh, $tbl_name, $tbl_engine);

# Show how to generate an AUTO_INCREMENT value and retrieve it using
# the database handle.  Then do same with statement handle.

$dbh->do ("INSERT INTO $tbl_name (seq) VALUES(NULL)");
$seq = $dbh->{mysql_insertid};
print "seq (using dbh): $seq\n";
$sth = $dbh->prepare ("INSERT INTO $tbl_name (seq) VALUES(NULL)");
$sth->execute ();
$seq = $sth->{mysql_insertid};
print "seq (using sth): $seq\n";
# ... can also get the value with $dbh in this case...
$seq = $dbh->{mysql_insertid};
print "seq (using dbh): $seq\n";

# Create an AUTO_INCREMENT value on a second statement handle.
# This should not affect the value available through the first statement
# handle.
$sth2 = $dbh->prepare ("INSERT INTO $tbl_name (seq) VALUES(NULL)");
$sth2->execute ();
$seq = $sth2->{mysql_insertid};
print "After creating AUTO_INCREMENT value on second statement handle:\n";
print "sth2 value: $seq\n";
$seq = $sth->{mysql_insertid};
print "sth value: $seq\n";


# Open a second connection and demonstrate that clients do not interfere
# with each other's AUTO_INCREMENT values.  Do first with server-side
# value (LAST_INSERT_ID() function), then with client-side value
# (mysql_insertid attribute).

my $dbh2 = DBI->connect ($dsn, $user_name, $password,
                         {PrintError => 0, RaiseError => 1, AutoCommit => 1});

# server-side...
gen_seq_val ($dbh, $tbl_name);
gen_seq_val ($dbh2, $tbl_name);
$seq = get_seq_val ($dbh2);
print "seq (connection 2): $seq\n";
$seq = get_seq_val ($dbh);
print "seq (connection 1): $seq\n";
print "(the value should be less for connection 1)\n";

# client-side...
gen_seq_val ($dbh, $tbl_name);
gen_seq_val ($dbh2, $tbl_name);
$seq = $dbh2->{mysql_insertid};
print "seq (connection 2): $seq\n";
$seq = $dbh->{mysql_insertid};
print "seq (connection 1): $seq\n";
print "(the value should be less for connection 1)\n";

$dbh2->disconnect ();

# Generate a number, then show that issuing another query may
# destroy the client-side value, even for queries that don't generate
# a new AUTO_INCREMENT number.

# HMM - seems not to happen for SELECT statements...

gen_seq_val ($dbh, $tbl_name);
$seq = $dbh->{mysql_insertid};
print "seq (with no intervening statement): $seq\n";

gen_seq_val ($dbh, $tbl_name);
$dbh->do ("SET \@x = 1");
$seq = $dbh->{mysql_insertid};
print "seq (with intervening SET statement): $seq\n";

gen_seq_val ($dbh, $tbl_name);
$dbh->do ("UPDATE $tbl_name SET seq = seq WHERE 1 = 0");
$seq = $dbh->{mysql_insertid};
print "seq (with intervening UPDATE statement): $seq\n";

gen_seq_val ($dbh, $tbl_name);
$sth = $dbh->prepare ("SELECT * FROM $tbl_name");
$sth->execute ();
$sth->finish ();
$seq = $dbh->{mysql_insertid};
print "seq (with intervening SELECT statement): $seq\n";

# Show that LAST_INSERT_ID(expr) produces a value that can be retrieved
# using the client-side mechanism, but only under some circumstances.
# It doesn't work for SET.

#@ _CLIENT_SIDE_FAILURE_
$dbh->do ("SET \@x = LAST_INSERT_ID(48)");
$seq = $dbh->{mysql_insertid};
#@ _CLIENT_SIDE_FAILURE_
print "client-side seq (after SET \@x = LAST_INSERT_ID(48)): $seq\n";
#@ _CLIENT_SIDE_SUCCESS_
$seq = $dbh->selectrow_array ("SELECT LAST_INSERT_ID()");
#@ _CLIENT_SIDE_SUCCESS_
print "server-side seq (after SET \@x = LAST_INSERT_ID(48)): $seq\n";
#$dbh->do ("UPDATE $tbl_name SET seq=LAST_INSERT_ID(seq+1) WHERE id = 3");
$seq = $dbh->{mysql_insertid};
print "seq (after SET \@x = LAST_INSERT_ID(48)): $seq\n";

# Generate an AUTO_INCREMENT value, disconnect, reconnect.
# This shows that you can't retrieve the value except by using
# the same connection.

gen_seq_val ($dbh, $tbl_name);

$dbh->disconnect ();
$dbh = DBI->connect ($dsn, $user_name, $password,
                     {PrintError => 0, RaiseError => 1, AutoCommit => 1});

$seq = get_seq_val ($dbh);
print "seq (after reconnecting): $seq\n";

# Compare server-side and client-side methods after issuing various
# AUTO_INCREMENT queries.

compare_methods ($dbh, "INSERT INTO $tbl_name (seq) VALUES(NULL)");
compare_methods ($dbh, "SET \@x = LAST_INSERT_ID(48)");
compare_methods ($dbh, "SELECT LAST_INSERT_ID(48)");

$dbh->disconnect ();

# ----------------------------------------------------------------------

# Given a database handle, drop and recreate the $tbl_name table.

sub init_table
{
my ($dbh, $tbl_name, $tbl_engine) = @_;

  $dbh->do ("DROP TABLE IF EXISTS $tbl_name");
  $dbh->do ("
          CREATE TABLE $tbl_name
          (seq INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (seq))
          ENGINE=$tbl_engine
      ");
  # now try SHOW CREATE TABLE to see if the engine is correct
  my ($junk, $str) = $dbh->selectrow_array ("SHOW CREATE TABLE $tbl_name");
  if ($str =~ /\)\s*ENGINE=(\S*)/)
  {
    my $new_tbl_engine = $1;
    #print "$tbl_engine = $new_tbl_engine?\n";
    return if lc ($tbl_engine) eq lc ($new_tbl_engine);
  }
  print "WARNING: ";
  print "Table $tbl_name was not created with requested engine $tbl_engine\n";
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

sub get_seq_val
{
my $dbh = shift;

  return ($dbh->selectrow_array ("SELECT LAST_INSERT_ID()"));
}

# Run a query, then compare the value returned by LAST_INSERT_ID()
# with that returned by $dbh->{mysql_insertid}.

sub compare_methods
{
my ($dbh, $stmt) = @_;
my ($serverside, $clientside);

  $dbh->do ($stmt);
  $clientside = $dbh->{mysql_insertid};
  $serverside = $dbh->selectrow_array ("SELECT LAST_INSERT_ID()");
  if ($serverside != $clientside)
  {
    print "PROBLEM: $stmt\n";
    print "server value ($serverside) != client value ($clientside)\n";
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
