<?php
# transaction.php: simple transaction demonstration

# By default, this creates an InnoDB table.  If you specify a storage
# engine on the command line, that will be used instead.  Normally,
# this should be a transaction-safe engine that is supported by your
# server.  However, you can pass a nontransactional storage engine
# to verify that rollback doesn't work properly for such engines.

# The script uses a table named "money" and drops it if necessary.
# Change the name if you have a valuable table with that name. :-)

require_once "Cookbook.php";

# Create the example table and populate it with a couple of rows

function init_table ($dbh, $tbl_engine)
{
  try
  {
    $dbh->exec ("DROP TABLE IF EXISTS money");
    $dbh->exec ("CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name))
                                   ENGINE = $tbl_engine");
    $dbh->exec ("INSERT INTO money (name, amt)
                                   VALUES('Eve',10)");
    $dbh->exec ("INSERT INTO money (name, amt)
                                   VALUES('Ida',0)");
  }
  catch (PDOException $e)
  {
    die ("Cannot initialize test table: " . $e->getMessage () . "\n");
  }
}

# Display the current contents of the example table

function display_table ($dbh)
{
  $sth = $dbh->query ("SELECT name, amt FROM money");
  while ($row = $sth->fetch ())
    print ("$row[0] has \$$row[1]\n");
}

$tbl_engine = "InnoDB";   # default storage engine
if ($argc > 1)
  $tbl_engine = $argv[1];
print ("Using storage engine $tbl_engine to test transactions\n");

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Cannot connect to server: " . $e->getMessage () . "\n");
}

# Run the transaction using statements grouped in a function

print ("----------\n");
print ("This transaction should succeed.\n");
print ("Table contents before transaction:\n");
init_table ($dbh, $tbl_engine);
display_table ($dbh);

#@ _DO_TRANSACTION_
try
{
  $dbh->beginTransaction ();
  $dbh->exec ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
  $dbh->exec ("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'");
  $dbh->commit ();
}
catch (Exception $e)
{
  print ("Transaction failed, rolling back. Error was:\n");
  print ($e->getMessage () . "\n");
  # empty exception handler in case rollback fails
  try
  {
    $dbh->rollback ();
  }
  catch (Exception $e2) { }
}
#@ _DO_TRANSACTION_

print ("Table contents after transaction:\n");
display_table ($dbh);

print ("----------\n");
print ("This transaction should fail.\n");
print ("Table contents before transaction:\n");
init_table ($dbh, $tbl_engine);
display_table ($dbh);

try
{
  $dbh->beginTransaction ();
  $dbh->exec ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
  $dbh->exec ("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'");
  $dbh->commit ();
}
catch (Exception $e)
{
  print ("Transaction failed, rolling back. Error was:\n");
  print ($e->getMessage () . "\n");
  # empty exception handler in case rollback fails
  try
  {
    $dbh->rollback ();
  }
  catch (Exception $e2) { }
}

print ("Table contents after transaction:\n");
display_table ($dbh);

$dbh = NULL;
?>
