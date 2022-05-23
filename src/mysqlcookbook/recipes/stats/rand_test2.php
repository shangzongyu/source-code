<?php
# rand_test2.php: create a frequency distribution of RAND() values.
# This provides a test of the randomness of RAND().

$nchoices = 10;   # how many different numbers to permit
$npicks = 1000;   # number of times to pick a number

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

# drop and recreate the t table, then populate it

$sth = $dbh->exec ("DROP TABLE IF EXISTS t");
$sth = $dbh->exec ("CREATE TABLE t (num INT, counter INT)");

# populate the table with rows numbered 1 through $nchoices, each
# initialized with a counter value of zero

for ($i = 1; $i <= $nchoices; $i++)
  $sth = $dbh->exec ("INSERT INTO t (num,counter) VALUES($i,0)");

# Now run a zillion picks and count how many times each item gets picked

# If the upper loop boundary is too high, the script may time out.

for ($i = 0; $i < $npicks; $i++)
{
  $sth = $dbh->query ("SELECT num FROM t ORDER BY RAND() LIMIT 1");
  $row = $sth->fetch ();
  # update count for selected value
  $sth = $dbh->exec ("UPDATE t SET counter = counter + 1
                      WHERE num = $row[0]");
}

# Print the resulting frequency distribution

$sth = $dbh->query ("SELECT num, counter FROM t ORDER BY num");
while (list ($num, $counter) = $sth->fetch ())
  printf ("%2d  %d\n", $num, $counter);

# Display total number of choices and standard deviation of distribution

$sth = $dbh->query ("SELECT SUM(counter), STD(counter) FROM t");
list ($n, $stddev) = $sth->fetch ();
print ("total number of selections: $n\n");
print ("standard deviation of selections: $stddev\n");

$dbh = NULL;
?>
