#!/usr/bin/python3
# test_pat.py: Read input lines, see which patterns they match.

import re
import sys

# Associate test names with corresponding patterns
patterns =  {
  "EMPTY":              '^$',
  "NONEMPTY":           '.',
  "NONEMPTY, NONWHITE": '\S',
  "UNSIGNED INTEGER":   '^\d+$',
  "INTEGER":            '^[-+]?\d+$',
  "FLOATING POINT":     '^[-+]?(\d+(\.\d*)?|\.\d+)$',
  "CREDIT CARD":        '^[- 0-9]+$',
  "ZIP CODE (5-digit)": '^\d{5}$',
  "ZIP+4 CODE":         '^\d{5}-\d{4}$',
  "ZIP or ZIP+4 CODE":  '^\d{5}(-\d{4})?$'
}

for line in sys.stdin:
  line = line.rstrip()
  print("Data value: %s" % (line))
  for test_name, pat in patterns.items():
    print("\t%s: %s" % (test_name, ("yes" if re.match(pat, line) else "no")))


"""
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
"""
