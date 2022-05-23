#!/usr/bin/perl
# validate_htwt.pl: Height/weight validation example.

# Assumes tab-delimited, linefeed-terminated input lines.

# Input columns and the actions to perform on them are as follows:
# 1: name; echo as given
# 2: birth; echo as given
# 3: height; validate as positive integer
# 4: weight; validate as positive integer

use strict;
use warnings;
use Cookbook_Utils;

while (<>)
{
  chomp;
  my ($name, $birth, $height, $weight) = split (/\t/, $_, 4);
  warn "line $.:height $height is not a positive integer\n"
                if !is_positive_integer ($height);
  warn "line $.:weight $weight is not a positive integer\n"
                if !is_positive_integer ($weight);
}
