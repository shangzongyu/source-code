<?php
# get_column_names.php: wrapper to demonstrate get_column_names()
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

print "Using get_column_names():\n";
print ("Columns in $db_name.$tbl_name table:\n");
$names = get_column_names ($dbh, $db_name, $tbl_name);
print (implode (", ", $names) . "\n");

# construct "all but" statement
print ("Construct statement to select all but data column:\n");
#@ _ALL_BUT_
$names = get_column_names ($dbh, $db_name, $tbl_name);
$stmt = "";
# construct list of columns to select: all but "data"
foreach ($names as $name)
{
  if ($name == "data")
    continue;
  if ($stmt != "") # put commas between column names
    $stmt .= ",";
  $stmt .= quote_identifier ($name);
}
$db_name = quote_identifier ($db_name);
$tbl_name = quote_identifier ($tbl_name);
$stmt = "SELECT $stmt FROM $db_name.$tbl_name";
#@ _ALL_BUT_
print ("$stmt\n");

$dbh = NULL;
?>
