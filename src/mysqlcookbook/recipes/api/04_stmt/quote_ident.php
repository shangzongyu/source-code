<?php
# quote_ident.php: demonstrate identifier quoting in PHP

require_once "Cookbook.php";
require_once "Cookbook_Utils.php"; # location of quote_identifier()

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Cannot connect to server: " . $e->getMessage () . "\n");
}

# This example uses database, table, and column names as identifiers,
# and quotes them as such

$db_name = "some db";
$tbl_name = "some`table";
$col_name = "some column`name";

#@ _USE_
$stmt = sprintf ("SELECT %s FROM %s.%s",
                 quote_identifier($col_name),
                 quote_identifier($db_name),
                 quote_identifier($tbl_name));
print ($stmt . "\n");

# This example uses database and table names as data values,
# and quotes them as such

$db_name = "cookbook";
$tbl_name = "profile";

#@ _IDENT_AS_DATA_
$sth = $dbh->prepare ("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS
                       WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?");
$sth->execute (array ($db_name, $tbl_name));
#@ _IDENT_AS_DATA_
foreach ($sth as $row)
  printf ("%s\n", $row[0]);

$dbh = NULL;
?>
