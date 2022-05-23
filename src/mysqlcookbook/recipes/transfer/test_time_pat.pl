#!/usr/bin/perl
# test_time_pat.pl: Read input lines, see which time patterns they match.

use strict;
use warnings;


my @patterns =  # Associate test names with corresponding patterns
(
  "hh:mm:ss",           '^\d{2}:\d{2}:\d{2}$',
  "hh:mm or hh:mm:ss",  '^\d{2}:\d{2}(:\d{2})?$'
);

while (<>)
{
  chomp;
  print "Data value: ($_)\n";
  for (my $i = 0; $i < @patterns - 1; $i += 2)
  {
    my $test_name = $patterns[$i];
    my $pat = $patterns[$i+1];
    print "\t$test_name: " . (/$pat/ ? "yes" : "no") . "\n";
  }
}
