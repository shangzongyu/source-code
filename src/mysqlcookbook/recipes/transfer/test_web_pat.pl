#!/usr/bin/perl
# test_web_pat.pl: Read input lines, see which web-related patterns they match.

use strict;
use warnings;

my @patterns =  # Associate test names with corresponding patterns
(
  # @ with nonempty strings on either side
  "Email test 1",         '.@.',
  # @ with nonempty strings not containing @ or space on either side
  "Email test 2",         '^[^@ ]+@[^@ ]+$',
  # @ with nonempty string not containing @ on left side, right
  # hand side must have at least two parts separated by a dot
  "Email test 3",         '^[^@ ]+@[^@ .]+\.[^@ .]+',
  # next one not case-insensitive, although it should be in production use
  "URL protocol prefix",  '^(http://|ftp://|mailto:)'
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
