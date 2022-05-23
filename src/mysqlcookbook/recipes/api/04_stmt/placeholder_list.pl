#!/usr/bin/perl
# placeholder_list.pl

use strict;
use warnings;

# Create a string of placeholder characters, with one ? character
# per element in an array of values.

# Array of values

my @values = (1, 2, 3, 4, 5);

my $str;

# Method 1: use x to "multiply" and array and join to put commas between
# elements

#@ _JOIN_METHOD_
$str = join (",", ("?") x @values);
#@ _JOIN_METHOD_

print "Method 1: $str\n";

# Method 2: successive concatenation

#@ _CONCAT_METHOD_1_
$str = "?" if @values;
$str .= ",?" for 1 .. @values-1;
#@ _CONCAT_METHOD_1_

print "Method 2: $str\n";

# Method 3: another successive concatenation method, using syntax that's
# less Perl-specific and more like what's found in other languages.

#@ _CONCAT_METHOD_2_
$str = "";
$str = "?" if @values;
for (my $i = 1; $i < @values; $i++)
{
  $str .= ",?";
}
#@ _CONCAT_METHOD_2_

print "Method 3: $str\n";
