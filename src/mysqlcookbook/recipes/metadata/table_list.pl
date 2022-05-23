#!/usr/bin/perl
# table_list.pl

# Demonstrate tables() method, which returns a list of the tables
# in the current database.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

my @tables;

#@ _TABLES_
@tables = $dbh->tables ();
#@ _TABLES_

print "Tables in current database:\n";
print join ("\n", @tables), "\n";

$dbh->disconnect ();
