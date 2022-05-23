<?php
# test_date.php: Pass each of the command line arguments to strtotime()
# to see how it interprets them.

# Try it from the command line like this, for example:
# php test_date.php now today "-1 day"

for ($i = 1; $i < $argc; $i++)
{
  printf ("%d: %s = %s\n", $i,
          $argv[$i],
          date ("Y-m-d H:i:s", strtotime ($argv[$i])));
}
?>
