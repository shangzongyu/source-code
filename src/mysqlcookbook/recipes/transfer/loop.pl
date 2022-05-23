#!/usr/bin/perl
# loop.pl: Typical input-processing loop.

# Assumes tab-delimited, linefeed-terminated input lines.

use strict;
use warnings;

while (<>)                # read each line
{
  chomp;
#@ _SPLIT_
  # split line at tabs, preserving all fields
  my @val = split (/\t/, $_, 10000);
#@ _SPLIT_
  for my $i (0 .. @val - 1) # iterate through fields in line
  {
    # ... test $val[$i] here ...
  }
}
