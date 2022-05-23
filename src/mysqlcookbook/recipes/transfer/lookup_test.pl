#!/usr/bin/perl
# lookup_test.pl: Illustrate various ways to use a lookup table
# to determine whether or not input values are listed in the table.

# The methods check values listed in an array.  You'd probably be more
# likely to use the inner part of each loop in an input processing loop
# that reads lines from a file.

# The lookup table name is determined by $tbl_name (default: "lookup_table").
# Change the variable value to use a different table.

# The tests are case sensitive.  To perform case-insensitive tests,
# convert the lookup values to lowercase, then test lowercased input
# values against them.  (Uppercase would work, too.)

use strict;
use warnings;
use Cookbook;

my $tbl_name = "lookup_table";

my $dbh = Cookbook::connect ();

# Create and populate the lookup table with a set of values

my @lookup_values = ("pig", "cat", "duck", "goat", "dog");

$dbh->do ("DROP TABLE IF EXISTS $tbl_name");
$dbh->do ("CREATE TABLE $tbl_name (val CHAR(10))");
foreach my $val (@lookup_values)
{
  $dbh->do ("INSERT INTO $tbl_name (val) VALUES(?)", undef, $val);
}

print "Legal lookup values: @lookup_values\n";

# The set of "input" values to be checked against the lookup table

my @input = ("snake", "dog", "sheep", "cat", "snake", "dog", "snake");

my $valid;

# Method 1: Issue individual query to check each input value

print "\nIssue lookup query for each input value:\n";

foreach my $val (@input)
{
#@ _QUERY_PER_VALUE_
  $valid = $dbh->selectrow_array (
             "SELECT COUNT(*) FROM $tbl_name WHERE val = ?",
             undef, $val);
#@ _QUERY_PER_VALUE_
  print "Value: $val (" . ($valid > 0 ? "good" : "bad") . ")\n";
}

# Method 2: Read contents of lookup table into a hash, using each value
# as a hash key.  Check input values by performing key existence test.

{ # scope begin

print "\nRead lookup table into hash, use hash to check input values:\n";

#@ _READ_LOOKUP_TABLE_
my %members;  # hash for lookup values
my $sth = $dbh->prepare ("SELECT val FROM $tbl_name");
$sth->execute ();
while (my ($val) = $sth->fetchrow_array ())
{
  $members{$val} = 1;
}
#@ _READ_LOOKUP_TABLE_

foreach my $val (@input)
{
#@ _LOOKUP_VIA_HASH_KEY_
  $valid = exists ($members{$val});
#@ _LOOKUP_VIA_HASH_KEY_
  print "Value: $val (" . ($valid ? "good" : "bad") . ")\n";
}

} # scope end

# Method 3: Use a hash as a cache of those input values that have been
# seen.  Look up each value as it's encountered, storing the value as
# a hash key, and true/false as the hash value to indicate whether or
# not the value was present in the table.  The next time the value is
# encountered, it'll be in the hash and can be checked without issuing
# a query.

{ # scope begin

print "\nHash as cache of seen input values:\n";

#@ _HASH_AS_CACHE_1_
my %members;  # hash for lookup values
#@ _HASH_AS_CACHE_1_
foreach my $val (@input)
{
#@ _HASH_AS_CACHE_2_
  if (!exists ($members{$val})) # haven't seen this value yet
  {
    my $count = $dbh->selectrow_array (
                  "SELECT COUNT(*) FROM $tbl_name WHERE val = ?",
                  undef, $val);
    # store true/false to indicate whether value was found
    $members{$val} = ($count > 0);
  }
  $valid = $members{$val};
#@ _HASH_AS_CACHE_2_
  print "Value: $val (" . ($valid ? "good" : "bad") . ")\n";
}

} # scope end

$dbh->disconnect ();
