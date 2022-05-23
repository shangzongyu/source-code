#!/usr/bin/perl
# isoize_date.pl: Read input data, look for values that match
# a date pattern, convert them to ISO format. Also converts
# 2-digit years to 4-digit years, using a transition point of 70.
# By default, this looks for dates in MM-DD-[CC]YY format.
# Does not check whether dates actually are valid (for example,
# won't complain about 13-49-1928).

# Assumes tab-delimited, linefeed-terminated input lines.

use strict;
use warnings;

# transition point at which 2-digit XX year values are assumed to be
# 19XX (below that, they are treated as 20XX)
my $transition = 70;

while (<>)
{
  chomp;
  my @val = split (/\t/, $_, 10000);  # split, preserving all fields
  for my $i (0 .. @val - 1)
  {
    # look for strings in MM-DD-[CC]YY format
    next unless $val[$i] =~ /^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$/;

    my ($month, $day, $year) = ($1, $2, $3);
    # to interpret dates as DD-MM-[CC]YY instead, replace preceding
    # line with the following one:
    #my ($day, $month, $year) = ($1, $2, $3);

    # convert 2-digit years to 4 digits, then update value in array
    $year += ($year >= $transition ? 1900 : 2000) if $year < 100;
    $val[$i] = sprintf ("%04d-%02d-%02d", $year, $month, $day);
  }
  print join ("\t", @val) . "\n";
}
