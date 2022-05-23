<?php
# date_sent.php: fetch rows into object, refer to columns by name

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
#@ FRAG
  $sth = $dbh->query ("SELECT srcuser,
                       DATE_FORMAT(t,'%M %e, %Y') AS date_sent
                          FROM mail");
  while ($row = $sth->fetch (PDO::FETCH_OBJ))
    printf ("user: %s, date sent: %s\n", $row->srcuser, $row->date_sent);
#@ FRAG
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
