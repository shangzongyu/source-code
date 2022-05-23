#!/usr/bin/perl
# median.pl: median calculations

# median of a set of ordered values is defined here as:
# - if number of values n is odd: value (n-1)/2
# - if number of values n is even: (value n + value n+1)/2
# These formulas are appropriate for referring to elements in Perl arrays,
# which have an initial subscript of 0, not 1.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

# Create set of random values:
# - At least 5, but no more than 20 integers.
# - Each integer is randomly chosen in the range from 0 to 20.

my @val;
srand (time ());
my $n = 5 + int (rand (16));
print "There are $n values:\n";
foreach my $i (0 .. $n-1)
{
  push (@val, int (rand (21)));
}

# Create a table t (drop first if it exists)
# and populate it with sample values

$dbh->do (qq{ DROP TABLE IF EXISTS t });
$dbh->do (qq{ CREATE TABLE t (obs INT) });
foreach my $i (0 .. $n-1)
{
  $dbh->do (qq{ INSERT INTO t (obs) VALUES(?) }, undef, $val[$i]);
}

# Show sorted values to user (use <=> to sort numerically)

@val = sort ({ $a <=> $b } @val);
foreach my $i (0 .. $n-1)
{
  printf "%2d: %2d\n", $i+1, $val[$i];
}

# Compute median using function that selects the values from the table

print "median (using query): " .  median ($dbh, "cookbook", "t", "obs") . "\n";

$dbh->disconnect ();

# Compute median using just the array of values itself
# (remember that array indexes start at 0)

my $median;
# _MEDIAN_USING_ARRAY_
if (@val == 0)          # array is empty, median is undefined
{
  $median = undef;
}
elsif (@val % 2 == 1)   # array size is odd, median is middle number
{
  $median = $val[(@val-1)/2];
}
else                    # array size is even; median is average
{                       # of two middle numbers
  $median = ($val[@val/2 - 1] + $val[@val/2]) / 2;
}
# _MEDIAN_USING_ARRAY_
print "median (using array of values): $median\n";

# Perform median calculation:
# - Determine how many values there are
# - Print them (this is just so user can see what they are)
# - Use LIMIT to retrieve the values

#@ _MEDIAN_USING_FUNCTION_
sub median
{
my ($dbh, $db_name, $tbl_name, $col_name) = @_;
my ($count, $limit);

  $db_name = $dbh->quote_identifier ($db_name);
  $tbl_name = $dbh->quote_identifier ($tbl_name);
  $col_name = $dbh->quote_identifier ($col_name);

  $count = $dbh->selectrow_array (qq{
    SELECT COUNT($col_name) FROM $db_name.$tbl_name
  });
  return undef unless $count > 0;
  if ($count % 2 == 1)  # odd number of values; select middle value
  {
    $limit = sprintf ("LIMIT %d,1", ($count-1)/2);
  }
  else                  # even number of values; select middle two values
  {
    $limit = sprintf ("LIMIT %d,2", $count/2 - 1);
  }

  my $sth = $dbh->prepare (qq{
    SELECT $col_name FROM $db_name.$tbl_name ORDER BY $col_name $limit
  });
  $sth->execute ();
  my ($n, $sum) = (0, 0);
  while (my $ref = $sth->fetchrow_arrayref ())
  {
    ++$n;
    $sum += $ref->[0];
  }
  return $sum / $n;
}
#@ _MEDIAN_USING_FUNCTION_
