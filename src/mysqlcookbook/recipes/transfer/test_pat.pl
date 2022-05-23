#!/usr/bin/perl
# test_pat.pl: Read input lines, see which patterns they match.

use strict;
use warnings;

my @patterns =  # Associate test names with corresponding patterns
(
  "EMPTY",              '^$',
  "NONEMPTY",           '.',
  "NONEMPTY, NONWHITE", '\S',
  "UNSIGNED INTEGER",   '^\d+$',
  "INTEGER",            '^[-+]?\d+$',
  "FLOATING POINT",     '^[-+]?(\d+(\.\d*)?|\.\d+)$',
  "CREDIT CARD",        '^[- 0-9]+$',
  "ZIP CODE (5-digit)", '^\d{5}$',
  "ZIP+4 CODE",         '^\d{5}-\d{4}$',
  "ZIP or ZIP+4 CODE",  '^\d{5}(-\d{4})?$'
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
