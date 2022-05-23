<?php
# placeholder_list.php

# Create a string of placeholder characters, with one ? character
# per element in an array of values.

# Array of values

$values = array (1, 2, 3, 4, 5);

#@ _CONCAT_METHOD_
$str = "";
if (count ($values))
  $str = "?";
for ($i = 1; $i < count ($values); $i++)
  $str .= ",?";
#@ _CONCAT_METHOD_

print ("$str\n");
?>
