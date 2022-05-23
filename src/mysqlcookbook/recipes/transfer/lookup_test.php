<?php
# lookup_test.php: Demonstrate use of associative array for
# lookup/validation purposes.

# create array, add members to it, using values as keys

$members = array (
  "pig"  => 1,
  "cat"  => 1,
  "duck" => 1,
  "dog"  => 1
);

# show list of legal values

print ("Legal values: " . implode (" ", array_keys ($members)) . "\n");

# test some values to see whether they're in the array

print ("Test some values:\n");
$values = array ("cat", "snake");
foreach ($values as $val)
{
  if (isset ($members[$val]))
    print ($val . " (good)\n");
  else
    print ($val . " (bad)\n");
}
?>
