<?php
# rand_test.php: create a frequency distribution of RAND() values.
# This provides a test of the randomness of RAND().

# Method: Draw random numbers in the range from 0 to 1.0,
# and count how many of them occur in .1-sized intervals
# (0 up to .1, .1 up to .2, ..., .9 up *through* 1.0).

$npicks = 1000;   # number of times to pick a number
$bucket = array (); # buckets for counting picks in each interval

# Initialize $bucker array
for ($i = 0; $i < 10; $i++)
  $bucket[$i] = 0;

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

# Note: If the upper loop boundary is too high, the script may time out.

for ($i = 0; $i < $npicks; $i++)
{
  $sth = $dbh->query ("SELECT RAND()");
  list($val) = $sth->fetch ();
  $slot = (int) ($val * 10);
  if ($slot > 9)
    $slot = 9;        # put 1.0 in last slot
  ++$bucket[$slot];
}

$dbh = NULL;

# Print the resulting frequency distribution

for ($slot = 0; $slot < 10; $slot++)
  printf ("%2d  %d\n", $slot+1, $bucket[$slot]);
?>
