#!/usr/bin/perl
#@ _PROLOG_1_
# xml_to_mysql.pl: Read XML file into MySQL.
#@ _PROLOG_1_

# Records are assumed to be in <row> elements.
# Each row must have column elements that have the column names
# as element names and column values as element values.  For example:
# <row>
#   <id>38</id>
#   <name>Chopin</name>
# </row>

#@ _PROLOG_2_
use strict;
use warnings;
use DBI;
use XML::XPath;
#@ _PROLOG_2_
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "xml_to_mysql.pl";
my $usage = <<EOF;
Usage: $prog [options] db_name tbl_name xml_file

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

Required arguments:
db_name, tbl_name
    Name of database and table to load the data file into
xml_file
    Name of data file
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

@ARGV == 3 or die "$usage\n";
my $db_name = shift (@ARGV);
my $tbl_name = shift (@ARGV);
my $file_name = shift (@ARGV);

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

#@ _IMPORT_DOCUMENT_
# Open file for reading
my $xp = XML::XPath->new (filename => $file_name);
my $row_list = $xp->find ("//row");     # find set of <row> elements
print "Number of records: " . $row_list->size () . "\n";
foreach my $row ($row_list->get_nodelist ())    # loop through rows
{
  my @name; # array for column names
  my @val;  # array for column values
  my $col_list = $row->find ("*");              # child columns of row
  foreach my $col ($col_list->get_nodelist ())  # loop through columns
  {
    push (@name, $col->getName ());             # save column name
    push (@val, $col->string_value ());         # save column value
  }
  # construct INSERT statement, then execute it
  my $stmt = "INSERT INTO $tbl_name ("
             . join (",", @name)
             . ") VALUES ("
             . join (",", ("?") x scalar (@val))
             . ")";
  $dbh->do ($stmt, undef, @val);
}

$dbh->disconnect ();
#@ _IMPORT_DOCUMENT_
