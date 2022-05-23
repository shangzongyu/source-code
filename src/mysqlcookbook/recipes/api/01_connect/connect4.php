<?php
# connect4.php: connect to the MySQL server, specifying character set

try
{
#@ _FRAG_
  $dsn = "mysql:host=localhost;dbname=cookbook;charset=utf8";
#@ _FRAG_
  $dbh = new PDO ($dsn, "cbuser", "cbpass");
  print ("Connected\n");
}
catch (PDOException $e)
{
  die ("Cannot connect to server\n");
}
$dbh = NULL;
print ("Disconnected\n");
?>
