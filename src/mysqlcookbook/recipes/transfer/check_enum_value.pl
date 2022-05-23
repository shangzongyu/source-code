#!/usr/bin/perl
# check_enum_value.pl: Wrapper to demonstrate the check_enum_value()
# utility function that determines whether a value is a member of
# a given ENUM column.

# Usage: check_enum_value.pl db_name tbl_name col_name test_value
# (assumes cookbook database)

use strict;
use warnings;
use Cookbook;
use Cookbook_Utils;

@ARGV == 4 or die "Usage: $0 db_name, tbl_name col_name test_value\n";

my $db_name = shift (@ARGV);
my $tbl_name = shift (@ARGV);
my $col_name = shift (@ARGV);
my $val = shift (@ARGV);

my $dbh = Cookbook::connect ();

# Use this for single-value testing

my $valid = check_enum_value ($dbh, $db_name, $tbl_name, $col_name, $val);

print "$val "
      . ($valid ? "is" : "is not")
      . " a member of $tbl_name.$col_name\n";

# For bulk testing of lots of values, get the column metadata,
# construct a hash from the array of ENUM values, and use that for
# testing values.

#@ _BULK_ENUM_CHECK_SETUP_
my $ref = get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name);
my %members;
# convert hash key to consistent lettercase
map { $members{lc ($_)} = 1; } @{$ref->{values}};
#@ _BULK_ENUM_CHECK_SETUP_

# Normally, you'd put the following test in a loop to check each
# input value.

#@ _BULK_ENUM_CHECK_TEST_
$valid = exists ($members{lc ($val)});
#@ _BULK_ENUM_CHECK_TEST_
print "$val "
      . ($valid ? "is" : "is not")
      . " a member of $tbl_name.$col_name\n";

$dbh->disconnect ();
