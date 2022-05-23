<?php
# booksales.php: show how to use LAST_INSERT_ID(expr)

require_once "Cookbook.php";

$dbh = Cookbook::connect ();

$stmt = "INSERT INTO booksales (title,copies)
         VALUES('The Greater Trumps',LAST_INSERT_ID(1))
         ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1)";
$sth = $dbh->exec ($stmt);
$sth = $dbh->query ("SELECT LAST_INSERT_ID()");
list ($count) = $sth->fetch ();
print ("count: $count\n");

$dbh = NULL;
?>
