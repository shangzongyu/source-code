#!/usr/bin/perl
# check_set_value.pl: Wrapper to demonstrate check_set_value()
# utility function that determines whether a value is a legal
# value of a given SET column.

# Usage: check_set_value.pl db_name tbl_name col_name test_value

use strict;
use warnings;
use Cookbook;
use Cookbook_Utils;

@ARGV == 4 or die "Usage: $0 db_name tbl_name col_name test_value\n";

my $db_name = shift (@ARGV);
my $tbl_name = shift (@ARGV);
my $col_name = shift (@ARGV);
my $val = shift (@ARGV);

my $dbh = Cookbook::connect ();

my $valid = check_set_value ($dbh, $db_name, $tbl_name, $col_name, $val);

print "'$val' "
      . ($valid ? "is" : "is not")
      . " a valid $tbl_name.$col_name value\n";

# For bulk testing of lots of values, get the column metadata,
# construct a hash from the array of SET values, and use that for
# testing values.

#@ _BULK_SET_CHECK_SETUP_
my $ref = get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name);
my %members;
# convert hash key to consistent lettercase
map { $members{lc ($_)} = 1; } @{$ref->{values}};
#@ _BULK_SET_CHECK_SETUP_

# If any element of the test value isn't in the SET,
# the entire value is invalid

#@ _BULK_SET_CHECK_TEST_
$valid = 1;     # assume valid until we find out otherwise
foreach my $elt (split (/,/, lc ($val)))
{
  if (!exists ($members{$elt}))
  {
    $valid = 0; # value contains an invalid element
    last;
  }
}
#@ _BULK_SET_CHECK_TEST_
print "'$val' "
      . ($valid ? "is" : "is not")
      . " a valid $tbl_name.$col_name value\n";

$dbh->disconnect ();
