<?php
# check_enum_value.php: Wrapper to demonstrate check_enum_value()
# utility function that determines whether a value is a member of
# a given ENUM column.

# Usage: check_enum_value.php db_name tbl_name col_name test_value

require_once "Cookbook.php";
require_once "Cookbook_Utils.php";

if ($argc != 5)
  die ("Usage: check_enum_value.php db_name tbl_name col_name test_value\n");

$db_name = $argv[1];
$tbl_name = $argv[2];
$col_name = $argv[3];
$val = $argv[4];

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  print ("Cannot connect to server: " . $e->getMessage () . "\n");
  exit (1);
}

$valid = check_enum_value ($dbh, $db_name, $tbl_name, $col_name, $val);

print ("$val "
        . ($valid ? "is" : "is not")
        . " a member of $tbl_name.$col_name\n");

$dbh = NULL;
?>
