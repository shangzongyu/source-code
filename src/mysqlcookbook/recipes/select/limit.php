<?php
# limit.php: Demonstrate how quoting of LIMIT arguments in a prepared
# statement causes statement-execution failure

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
  # Execution here will fail because PDO quotes the LIMIT arguments
  # when binding them to the placeholders.
#@ _FRAG_
  $sth = $dbh->prepare ("SELECT * FROM profile LIMIT ?,?");
  $sth->execute (array (2, 4));
#@ _FRAG_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
