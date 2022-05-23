#!/usr/bin/perl
# rand_test2.pl: create a frequency distribution of RAND() values.
# This provides a test of the randomness of RAND().

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

my $nchoices = 10;    # how many different numbers to permit
my $npicks = 1000;    # number of times to pick a number

# drop and recreate the t table, then populate it

$dbh->do ("DROP TABLE IF EXISTS t");
$dbh->do ("CREATE TABLE t (num INT, counter INT)");

# populate the table with rows numbered 1 through nchoices, each
# initialized with a counter value of zero

for my $i (1 .. $nchoices)
{
  $dbh->do ("INSERT INTO t (num,counter) VALUES(?, 0)", undef, $i);
}

# Now run a zillion picks and count how many times each item gets picked

for my $i (1 .. $npicks)
{
  my $num = $dbh->selectrow_array (
              "SELECT num FROM t ORDER BY RAND() LIMIT 1");
  # update count for selected value
  $dbh->do ("UPDATE t SET counter = counter + 1 WHERE num = ?", undef, $num);
}

# Print the resulting frequency distribution

my $sth = $dbh->prepare ("SELECT num, counter FROM t ORDER BY num");
$sth->execute ();
while (my ($num, $counter) = $sth->fetchrow_array ())
{
  printf "%2d  %d\n", $num, $counter;
}

# Display total number of choices and standard deviation of distribution

my ($n, $stddev) =
  $dbh->selectrow_array ("SELECT SUM(counter), STD(counter) FROM t");
print "total number of selections: $n\n";
print "standard deviation of selections: $stddev\n";

$dbh->disconnect ();
