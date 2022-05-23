#!/usr/bin/perl
# err_disable.pl: demonstrate how to disable RaiseError selectively

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

die "Usage: $0 user_name password\n" unless @ARGV == 2;

#@ _FRAG_
my $user_name = shift (@ARGV);
my $password = shift (@ARGV);
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, $user_name, $password, $conn_attrs);
$dbh->{RaiseError} = 0; # disable automatic termination on error
print "Enter statements to execute, one per line; terminate with Control-D\n";
while (<>)              # read and execute queries
{
  $dbh->do ($_) or warn "Statement failed: $DBI::errstr ($DBI::err)\n";
}
#@ _FRAG_
$dbh->disconnect ();
