#!/usr/bin/perl
# regression.pl: Read X/Y pairs from stdin, compute least-squares regression

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

my $meanX = $sumX / $n;
my $meanY = $sumY / $n;

printf "N                = %d\n", $n;
printf "X mean           = %.3f\n", $meanX;
printf "X sum            = %.3f\n", $sumX;
printf "X sum of squares = %.3f\n", $sumXX;
printf "Y mean           = %.3f\n", $meanY;
printf "Y sum            = %.3f\n", $sumY;
printf "Y sum of squares = %.3f\n", $sumYY;
printf "X*Y sum          = %.3f\n", $sumXY;

# Calculate slope (b), intercept (a)

my $b = ($n*$sumXY - $sumX*$sumY) / ($n*$sumXX - $sumX*$sumX);
my $a = ($meanY - $b*$meanX);

print "\n";
printf "slope            = %.3f\n", $b;
printf "intercept        = %.3f\n", $a;
print "\n";
printf "regression: Y = %.3fX + %.3f\n", $b, $a;
