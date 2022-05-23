#!/usr/bin/perl
# test_integer.pl: Exercise the integer-testing library functions.

use strict;
use warnings;
use Cookbook_Utils;

my @val =
(
  "",
  "x",
  "-1",
  "0",
  "+1",
  "1",
  "-1.1",
  "+1.1",
  "1.1",
  ".1",
);

print "value  integer  unsigned int  positive int\n";
while (@val)
{
  my $val = shift (@val);   # value to test
  my $verdict = (is_integer ($val) ? "yes" : "no");
  my $u_verdict = (is_unsigned_integer ($val) ? "yes" : "no");
  my $p_verdict = (is_positive_integer ($val) ? "yes" : "no");
  printf "%5s  %-7s  %-8s      %s\n",
         $val, $verdict, $u_verdict, $p_verdict;
}
