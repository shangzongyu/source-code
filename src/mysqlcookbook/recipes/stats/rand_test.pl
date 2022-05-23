#!/usr/bin/perl
# rand_test.pl: create a frequency distribution of RAND() values.
# This provides a test of the randomness of RAND().

# Method: Draw random numbers in the range from 0 to 1.0,
# and count how many of them occur in .1-sized intervals
# (0 up to .1, .1 up to .2, ..., .9 up *through* 1.0).

use strict;
use warnings;
use Cookbook;

my $npicks = 1000; # number of times to pick a number
my @bucket;        # buckets for counting picks in each interval

my $dbh = Cookbook::connect ();

for my $i (1 .. $npicks)
{
  my $val = $dbh->selectrow_array ("SELECT RAND()");
  my $slot = int ($val * 10);
  $slot = 9 if $slot > 9;   # put 1.0 in last slot
  ++$bucket[$slot];
}

$dbh->disconnect ();

# Print the resulting frequency distribution

for my $slot (0 .. 9)
{
  printf "%2d  %d\n", $slot+1, $bucket[$slot];
}
