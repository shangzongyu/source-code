#!/usr/bin/perl
#@ _PROLOG_
# make_date_list.pl: create a table with an entry for every date in
# a given date range.  The table can be used in a LEFT JOIN when
# producing a summary, to ensure that every date appears in the
# summary, regardless of whether the data to be summarized actually
# contains any values for a given day.

# Usage: make_date_list.pl db_name tbl_name col_name min_date max_date

use strict;
use warnings;
use DBI;
#@ _PROLOG_
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

# ----------------------------------------------------------------------

my $prog = "make_date_list.pl";
my $usage = <<EOF;
Usage: make_date_list.pl db_name tbl_name col_name min_date max_date

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
EOF

# Variables for command line options - all undefined initially
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

#@ _GET_ARGS_
# Check number of arguments

@ARGV == 5 or die "$usage\n";
my ($db_name, $tbl_name, $col_name, $min_date, $max_date) = @ARGV;
#@ _GET_ARGS_

# Perform minimal tests for ISO-format dates

$min_date =~ /^\d+\D\d+\D\d+$/
  or die "Minimum date $min_date is not in ISO format\n";
$max_date =~ /^\d+\D\d+\D\d+$/
  or die "Maximum date $max_date is not in ISO format\n";

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

#@ _GENERATE_TABLE_
# Determine the number of days spanned by the date range.

my $days = $dbh->selectrow_array (qq{
  SELECT DATEDIFF(?,?) + 1
}, undef, $max_date, $min_date);

print "Minimum date: $min_date\n";
print "Maximum date: $max_date\n";
print "Number of days spanned by range: $days\n";
die "Date range is too small\n" if $days < 1;

$db_name = $dbh->quote_identifier ($db_name);
$tbl_name = $dbh->quote_identifier ($tbl_name);
$col_name = $dbh->quote_identifier ($col_name);

# Drop table if it exists, then recreate it

$dbh->do (qq{
  DROP TABLE IF EXISTS $db_name.$tbl_name
});
$dbh->do (qq{
  CREATE TABLE $db_name.$tbl_name
  ($col_name DATE NOT NULL, PRIMARY KEY ($col_name))
});

# Populate table with each date in the date range

my $sth = $dbh->prepare (qq{
  INSERT INTO $db_name.$tbl_name ($col_name) VALUES(? + INTERVAL ? DAY)
});
foreach my $i (0 .. $days-1)
{
  $sth->execute ($min_date, $i);
}
#@ _GENERATE_TABLE_

$dbh->disconnect ();
