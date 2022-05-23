#!/usr/bin/perl
# lookup_time.pl: Rough test of hash versus array lookups.

# - Construct a hash with n keys
# - Construct an array with n keys
# - Perform n lookups on each

# This is a very crude test.  Even so, I find the results are often
# striking even for n = 1000.

use strict;
use warnings;

my $n = 10000;  # number of keys to use/lookups to perform

my %hash;
my @array;

for my $i (0 .. $n)
{
  $hash{$i} = 1;
  push (@array, $i);
}

print scalar (localtime (time)), "\n";
print "Performing $n hash lookups...\n";
for my $i (0 .. $n)
{
  die "logic error" unless exists ($hash{$i});
}
print "Done.\n";
print scalar (localtime (time)), "\n";
print "Performing $n array lookups...\n";
for my $i (0 .. $n)
{
  die "logic error" unless grep (/^$i$/, @array);
}
print "Done.\n";
print scalar (localtime (time)), "\n";
