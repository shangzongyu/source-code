<?php
# leap-native.php: Leap-year test using PHP native facilities

# set up an array of test dates

$date_array = array
(
  "1899-01-01",
  "1900-01-01",
  "1999-01-01",
  "2000-01-01",
  "1963-01-01",
  "1964-01-01"
);


foreach ($date_array as $date)
{
#@ _LEAP_TEST_
  # prevent date () from complaining about not knowing time zone
  date_default_timezone_set ("UTC");
  $is_leap = date ("L", strtotime ($date));
#@ _LEAP_TEST_
  print ("$date: is leap $is_leap\n");
}
?>
