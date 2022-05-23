#!/usr/bin/perl
# tracing.pl: enable tracing (after connecting successfully)

use strict;
use warnings;
use DBI;
my $dsn = "DBI:mysql:host=localhost;database=cookbook";

my $conn_attrs = {PrintError => 0, RaiseError => 0, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass", $conn_attrs);
print "trace level 1\n";
DBI->trace (1);
$dbh->do (qq{ DROP TABLE my_table1 });
# elevate trace level
print "trace level 3\n";
DBI->trace (3);
$dbh->do (qq{ DROP TABLE my_table2 });
# disable tracing
DBI->trace (0);
$dbh->disconnect ();
