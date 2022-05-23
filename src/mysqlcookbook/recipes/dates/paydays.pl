#!/usr/bin/perl
# paydays.pl: Find all the paydays of the year 2021, assuming that
# they fall on the 2nd and 4th Thursdays of each month

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

# Run a loop to construct the first day of the month for each month.
# Run a query based on each first-of-month date.

#@ _LOOP_
my $year = 2021;
print "MM/YYYY   2nd Thursday   4th Thursday\n";
foreach my $month (1..12)
{
  my $first = sprintf ("%04d-%02d-01", $year, $month);
  my ($thu2, $thu4) = $dbh->selectrow_array (qq{
                  SELECT
                    DATE_ADD(
                      DATE_ADD(?,INTERVAL 5-DAYOFWEEK(?) DAY),
                      INTERVAL IF(DAYOFWEEK(?) <= 5, 7, 14) DAY),
                    DATE_ADD(
                      DATE_ADD(?,INTERVAL 5-DAYOFWEEK(?) DAY),
                      INTERVAL IF(DAYOFWEEK(?) <= 5, 21, 28) DAY)
                }, undef, $first, $first, $first, $first, $first, $first);
  printf "%02d/%04d   %s     %s\n", $month, $year, $thu2, $thu4;
}
#@ _LOOP_

$dbh->disconnect ();
