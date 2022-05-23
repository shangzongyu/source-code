#!/usr/bin/perl
# parse_date.pl: Parse date values and test their validity.

# Converts 2-digit years to 4-digit using these rules:
# 70 .. 99 -> 1970 .. 1999
# 00 .. 69 -> 2000 .. 2069

use strict;
use warnings;
use Cookbook_Utils;

sub is_legal_date
{
my ($year, $month, $day) = @_;

  # do the easy tests first
  return 0 if $year < 0 || $month < 1 || $day < 1;
  return 0 if $month > 12;
  # if year < 100, we don't really know the date for sure.
  # convert to 4-digit using MySQL rule
  $year += ($year >= 70 ? 1900 : 2000) if $year < 100;
  return 0 if $day > days_in_month ($year, $month);
  # it appears to be legal...
  return 1;
}

my $date;
my @f;

while (defined ($date = <>))
{
  next if $date =~ /^#/;    # skip comments
  chomp ($date);
  print "Date: $date\n";
  # parse using "-" separator
  (@f) = ($date =~ /^(\d+)-(\d+)-(\d+)$/);
  printf "  %slegal using - separator\n", @f == 3 ? "" : "il";
  # parse using "/" separator
  (@f) = ($date =~ /^(\d+)\/(\d+)\/(\d+)$/);
  printf "  %slegal using / separator\n", @f == 3 ? "" : "il";
  # parse using any nondigit separator
  (@f) = ($date =~ /^(\d+)\D(\d+)\D(\d+)$/);
  printf "  %slegal using any nondigit separator\n", @f == 3 ? "" : "il";
  # assuming that the date is parsable under the most liberal standard
  # (any nondigit delimiter), test whether it seems to conform to
  # ISO 8601, US, or British date formats.
  printf "  legal as ISO 8601: %s",
         is_legal_date ($f[0], $f[1], $f[2]) ? "yes" : "no";
  printf "  US: %s",
         is_legal_date ($f[2], $f[0], $f[1]) ? "yes" : "no";
  printf "  British: %s",
         is_legal_date ($f[2], $f[1], $f[0]) ? "yes" : "no";
  print "\n";
}
