<?php
# dup_count.php: generate query to identify and count duplicate values

# Given database and table names and an array of one or more column
# names, return a query that can be executed to count duplicate values
# for those columns.

function make_dup_count_query ($db_name, $tbl_name, $col_name)
{
  return (
        "SELECT COUNT(*)," . implode (",", $col_name)
      . "\nFROM $db_name.$tbl_name"
      . "\nGROUP BY " . implode (",", $col_name)
      . "\nHAVING COUNT(*) > 1"
  );
}

$str = make_dup_count_query ("cookbook", "profile", array ("cats", "color"));
print ("$str\n");
?>
