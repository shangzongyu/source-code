<?php
# connect.php: connect to the MySQL server

#@ _FRAG_
#@ _FRAG2_
try
{
  $dsn = "mysql:host=localhost;dbname=cookbook";
  $dbh = new PDO ($dsn, "cbuser", "cbpass");
  print ("Connected\n");
}
catch (PDOException $e)
{
  die ("Cannot connect to server\n");
}
#@ _FRAG2_
$dbh = NULL;
print ("Disconnected\n");
#@ _FRAG_
?>
