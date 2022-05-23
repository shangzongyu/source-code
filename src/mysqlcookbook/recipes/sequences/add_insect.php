<?php
# add_insect.php: demonstrate client-side lastInsertId() database handle
# method for getting the most recent AUTO_INCREMENT value.

require_once "Cookbook.php";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Cannot connect to server: " . $e->getMessage () . "\n");
}

try
{
#@ _INSERT_ID_
  $dbh->exec ("INSERT INTO insect (name,date,origin)
               VALUES('moth','2014-09-14','windowsill')");
  $seq = $dbh->lastInsertId ();
#@ _INSERT_ID_
  print ("seq: $seq\n");
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
