#!/usr/bin/perl
# correlation.pl: Read X/Y pairs from stdin, compute correlation coefficient

# Input is assumed to consist of lines containing two whitespace-separated
# numbers.  Script won't work correctly if that assumption is violated.

use strict;
use warnings;

my $n = 0;
my $sumX = 0;
my $sumXX = 0;
my $sumY = 0;
my $sumYY = 0;
my $sumXY = 0;

while (<>)
{
  my ($x, $y) = /^\s*(\S+)\s+(\S+)/;
  ++$n;
  $sumX += $x;
  $sumXX += $x * $x;
  $sumY += $y;
  $sumYY += $y * $y;
  $sumXY += $x * $y
}
die "No input\n" if $n == 0;


printf "N                = %d\n", $n;
printf "X sum            = %.3f\n", $sumX;
printf "X sum of squares = %.3f\n", $sumXX;
printf "Y sum            = %.3f\n", $sumY;
printf "Y sum of squares = %.3f\n", $sumYY;
printf "X*Y sum          = %.3f\n", $sumXY;

# Calculate slope (b), intercept (a)

my $r = ($n*$sumXY - $sumX*$sumY)
    / sqrt (($n*$sumXX - $sumX*$sumX) * ($n*$sumYY - $sumY*$sumY));

printf "correlation      = %.3f\n", $r;
