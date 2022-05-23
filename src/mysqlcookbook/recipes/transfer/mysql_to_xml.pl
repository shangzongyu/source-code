#!/usr/bin/perl
#@ _PROLOG_
# mysql_to_xml.pl: Given a database and table name,
# dump the table to the standard output in XML format.

use strict;
use warnings;
use DBI;
use XML::Generator::DBI;
use XML::Handler::YAWriter;
#@ _PROLOG_
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "mysql_to_xml.pl";
my $usage = <<EOF;
Usage: $prog [options] [db_name]

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
EOF

# Variables for command line options - all undefined initially.
my $help;
my ($host_name, $password, $port_num, $socket_name, $user_name, $db_name);
my ($stmt, $tbl_name);

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
  "table|t=s"     => \$tbl_name     # table to export
) or die "$usage\n";

die "$usage\n" if defined ($help);

$db_name = shift (@ARGV) if @ARGV;

# One of --execute or --table must be specified, but not both
die "You must specify a query or a table name\n\n$usage\n"
  unless defined ($stmt) || defined ($tbl_name);
die "You cannot specify both a query and a table name\n\n$usage\n"
  if defined ($stmt) && defined ($tbl_name);

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

#@ _EXPORT_QUERY_
# Create output writer; "-" means "standard output"
my $out = XML::Handler::YAWriter->new (AsFile => "-");
# Set up connection between DBI and output writer
my $gen = XML::Generator::DBI->new (
  dbh         => $dbh,    # database handle
  Handler     => $out,    # output writer
  RootElement => "rowset" # document root element
);

# If table name was given, use it to create query that selects entire table.
# Split on dots in case it's a qualified name, to quote parts separately.
$stmt = "SELECT * FROM " . $dbh->quote_identifier (split (/\./, $tbl_name))
  if defined ($tbl_name);

# Issue query and write XML
$gen->execute ($stmt);

$dbh->disconnect ();
#@ _EXPORT_QUERY_
