#!/usr/bin/perl
# monddyyyy_to_iso.pl: Convert dates from mon[.] dd, yyyy to ISO format.

# Assumes tab-delimited, linefeed-terminated input

use strict;
use warnings;

my %map =   # map 3-char month abbreviations to numeric month
(
  "jan" => 1, "feb" => 2, "mar" => 3, "apr" => 4, "may" => 5, "jun" => 6,
  "jul" => 7, "aug" => 8, "sep" => 9, "oct" => 10, "nov" => 11, "dec" => 12
);

while (<>)
{
  chomp;
  my @val = split (/\t/, $_, 10000);    # split, preserving all fields
  for my $i (0 .. @val - 1)
  {
    # reformat the value if it matches the pattern, otherwise assume
    # that it's not a date in the required format and leave it alone
    if ($val[$i] =~ /^([^.]+)\.? (\d+), (\d+)$/)
    {
      # use lowercase month name
      my ($month, $day, $year) = (lc ($1), $2, $3);
#@ _CHECK_VALIDITY_
      if (exists ($map{$month}))
#@ _CHECK_VALIDITY_
      {
        $val[$i] = sprintf ("%04d-%02d-%02d", $year, $map{$month}, $day);
      }
      else
      {
        # warn, but don't reformat
        warn "$val[$i]: bad date?\n";
      }
    }
  }
  print join ("\t", @val) . "\n";
}
