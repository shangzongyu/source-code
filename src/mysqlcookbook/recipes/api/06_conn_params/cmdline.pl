#!/usr/bin/perl
# cmdline.pl: demonstrate command-line option parsing in Perl

use strict;
use warnings;
use DBI;

use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

# connection parameters - all missing (undef) by default
my $host_name;
my $password;
my $user_name;

GetOptions (
  # =s means a string value is required after the option
  "host|h=s"     => \$host_name,
  "password|p=s" => \$password,
  "user|u=s"     => \$user_name
) or exit (1);  # no error message needed; GetOptions() prints its own

# any nonoption arguments remain in @ARGV
# and can be processed here as necessary

# construct data source name
my $dsn = "DBI:mysql:database=cookbook";
$dsn .= ";host=$host_name" if defined ($host_name);

# connect to server
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, $user_name, $password, $conn_attrs);
print "Connected\n";

$dbh->disconnect ();
print "Disconnected\n";
