#!/usr/bin/perl
# connect.pl: connect to the MySQL server

use strict;
use warnings;
use DBI;

my $dsn = "DBI:mysql:host=localhost;database=cookbook";
#@ _CONNECT_
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass")
            or die "Cannot connect to server\n";
#@ _CONNECT_
print "Connected\n";
$dbh->disconnect ();
print "Disconnected\n";
