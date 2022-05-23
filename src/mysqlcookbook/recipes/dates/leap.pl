#!/usr/bin/perl
# leap.pl: Leap-year test of ISO date strings

use strict;
use warnings;

# days_in_month() - given an ISO-format date, determine the number
# of days in the month in which the date occurs

#@ _DAYS_IN_MONTH_
sub days_in_month
{
my $date = shift;
my $year = substr ($date, 0, 4);
my $month = substr ($date, 5, 2); # month, 1-based
my @days_in_month = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
my $days = $days_in_month[$month-1];
my $is_leap = ($year % 4 == 0) && ($year % 100 != 0 || $year % 400 == 0);

  $days++ if $month == 2 && $is_leap; # add a day for Feb of leap years
  return $days;
}
#@ _DAYS_IN_MONTH_

# ----------------------------------------------------------------------

# set up an array of test dates

my @date_array =
(
  "1899-01-01",
  "1900-01-01",
  "1999-01-01",
  "2000-01-01",
  "1963-01-01",
  "1964-01-01"
);

my ($date, $year, $is_leap, $days_in_year);

foreach $date (@date_array)
{
#@ _LEAP_TEST_
  $year = substr ($date, 0, 4);
  $is_leap = ($year % 4 == 0) && ($year % 100 != 0 || $year % 400 == 0);
#@ _LEAP_TEST_
  print "$date $year $is_leap\n";
#@ _YEAR_LENGTH_TEST_
  $year = substr ($date, 0, 4);
  $is_leap = ($year % 4 == 0) && ($year % 100 != 0 || $year % 400 == 0);
  $days_in_year = ($is_leap ? 366 : 365);
#@ _YEAR_LENGTH_TEST_
  print "$date $year $days_in_year days\n";
}

foreach $date (@date_array, "1900-02-01", "1999-02-01", "2000-02-01")
{
  print "Month for $date has " . days_in_month ($date) . " days\n";
}
