#!/usr/bin/perl
# get_column_names.pl: wrapper to demonstrate get_column_names()
# utility routine

# Assumes that you've created the "image" table!

use strict;
use warnings;
use Cookbook;
use Cookbook_Utils;

my $db_name = "cookbook";
my $tbl_name = "image";

my @names;

my $dbh = Cookbook::connect ();

{ # begin scope

print "Using get_column_names()\n";
print "Columns in $db_name.$tbl_name table:\n";
my @names = get_column_names ($dbh, $db_name, $tbl_name);
print join (", ", @names), "\n";

} # end scope

{ # begin scope

print "Construct statement to select all but data column:\n";
#@ _ALL_BUT_
my @names = get_column_names ($dbh, $db_name, $tbl_name);
@names = map { $dbh->quote_identifier ($_) } grep (!/^data$/, @names);
$db_name = $dbh->quote_identifier ($db_name);
$tbl_name = $dbh->quote_identifier ($tbl_name);
my $stmt = "SELECT " . join (",", @names) . " FROM $db_name.$tbl_name";
#@ _ALL_BUT_
print "$stmt\n";

} # end scope

$dbh->disconnect ();
