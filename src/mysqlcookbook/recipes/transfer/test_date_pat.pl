#!/usr/bin/perl
# test_date_pat.pl: Read input lines, see which date patterns they match.

use strict;
use warnings;


my @patterns =  # Associate test names with corresponding patterns
(
  "ISO date, - delimiter",          '^\d{4}-\d{2}-\d{2}$',
  "ISO date, - or / delimiter",     '^\d{4}[-\/]\d{2}[-\/]\d{2}$',
  "ISO date, nondigit delimiter",   '^\d{4}\D\d{2}\D\d{2}$',
  "3 sets of digits",               '^\d+\D\d+\D\d+$',
  "[CC]YY-[M]M-[D]D date",          '^\d{2}(\d{2})?\D\d{1,2}\D\d{1,2}$',
  "MM-DD-YY/DD-MM-YY date",         '^\d{2}-\d{2}-\d{2}$'
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
