<?php
# harness.php: test harness for Cookbook.php library

# Does not catch exceptions, so this script simply dies if
# a connect error occurs.

require_once "Cookbook.php";

$dbh = Cookbook::connect ();
print ("Connected\n");
$dbh = NULL;
print ("Disconnected\n");
?>
