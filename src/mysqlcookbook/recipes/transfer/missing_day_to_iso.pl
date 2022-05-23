#!/usr/bin/perl
# missing_day_to_iso.pl: Convert dates in mon/year format to ISO format
# with a day part of 00.

use strict;
use warnings;

#@ _MONTH_MAP_
my %map =   # map 3-char month abbreviations to numeric month
(
  "jan" => 1, "feb" => 2, "mar" => 3, "apr" => 4, "may" => 5, "jun" => 6,
  "jul" => 7, "aug" => 8, "sep" => 9, "oct" => 10, "nov" => 11, "dec" => 12
);
#@ _MONTH_MAP_

my @input = ("Feb/2001", "Mar/1988", "Dec/1889", "Jul/1934");

foreach my $val (@input)
{
  print "Original: $val\n";
#@ _REFORMAT_
  if ($val =~ /^([a-z]{3})\/(\d{4})$/i)
  {
    my ($m, $y) = (lc ($1), $2); # use lowercase month name
    $val = sprintf ("%04d-%02d-00", $y, $map{$m})
  }
#@ _REFORMAT_
  print "Reformatted: $val\n";
}
