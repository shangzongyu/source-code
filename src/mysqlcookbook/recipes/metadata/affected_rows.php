<?php
# affected_rows.php

require_once "Cookbook.php";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Error message: " . $e->getMessage () . "\n");
}
try
{
  $stmt = "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'";
#@ _FRAG_1_
  $count = $dbh->exec ($stmt);
  printf ("Number of rows updated: %d\n", $count);
#@ _FRAG_1_
#@ _FRAG_2_
  $sth = $dbh->prepare ($stmt);
  $sth->execute ();
  printf ("Number of rows updated: %d\n", $sth->rowCount ());
#@ _FRAG_2_
}
catch (PDOException $e)
{
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;

# illustrate how to get rows-matched counts rather than rows-changed counts

try
{
#@ _MYSQL_ATTR_FOUND_ROWS_
  $dsn = "mysql:host=localhost;dbname=cookbook";
  $dbh = new PDO ($dsn, "cbuser", "cbpass",
                  array (PDO::MYSQL_ATTR_FOUND_ROWS => 1));
#@ _MYSQL_ATTR_FOUND_ROWS_
}
catch (PDOException $e)
{
  die ("Error message: " . $e->getMessage () . "\n");
}

try
{
  # this statement changes no rows, but the row count should still
  # be nonzero due to the use of rows-matched counts
  $stmt = "UPDATE limbs SET arms = 0 WHERE arms = 0";
  $count = $dbh->exec ($stmt);
  printf ("Number of rows updated: %d\n", $count);
}
catch (PDOException $e)
{
  print ("Error message: " . $e->getMessage () . "\n");
}
?>
