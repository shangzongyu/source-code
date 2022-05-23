<?php
# get_column_info.php: wrapper to demonstrate get_column_info()
# utility routine

# Assumes that you've created the "image" table!

require_once "Cookbook.php";
require_once "Cookbook_Utils.php";

$db_name = "cookbook";
$tbl_name = "image";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  print ("Cannot connect to server: " . $e->getMessage () . "\n");
  exit (1);
}

print "Using get_column_info():\n";
print ("Column information for $db_name.$tbl_name table:\n");
$info = get_column_info ($dbh, $db_name, $tbl_name);
print_r ($info);

$dbh = NULL;
?>
