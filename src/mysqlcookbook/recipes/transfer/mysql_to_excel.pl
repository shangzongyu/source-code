#!/usr/bin/perl
#@ _PROLOG_
# mysql_to_excel.pl: Given a database and table name,
# dump the table to the standard output in Excel format.

use strict;
use warnings;
use DBI;
use Spreadsheet::ParseExcel::Simple;
use Spreadsheet::WriteExcel::FromDB;
#@ _PROLOG_
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "mysql_to_excel.pl";
my $usage = <<EOF;
Usage: $prog [options] db_name tbl_name

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

# Variables for command line options - all undefined initially.
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

#@ _GET_DB_TBL_NAMES_
@ARGV == 2 or die "$usage\n";
my $db_name = shift (@ARGV);
my $tbl_name = shift (@ARGV);
#@ _GET_DB_TBL_NAMES_

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

#@ _EXPORT_TABLE_
my $ss = Spreadsheet::WriteExcel::FromDB->read ($dbh, $tbl_name);
binmode (STDOUT);
print $ss->as_xls ();
#@ _EXPORT_TABLE_
