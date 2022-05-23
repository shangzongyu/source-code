<?php
# get_rs_meta.php: run a statement and display its result set metadata

# The program runs a default statement, which can be overridden by supplying
# a statement as an argument on the command line.

require_once "Cookbook.php";

#@ _DEFAULT_STATEMENT_
$stmt = "SELECT name, birth FROM profile";
#@ _DEFAULT_STATEMENT_
# override statement with command line argument if one was given
if ($argc > 1)
  $stmt = $argv[1];

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  print ("Error message: " . $e->getMessage () . "\n");
  exit (1);
}

try
{
#@ _DISPLAY_METADATA_
  print ("Statement: $stmt\n");
  $sth = $dbh->prepare ($stmt);
  $sth->execute ();
  # metadata information becomes available at this point ...
  $ncols = $sth->columnCount ();
  print ("Number of columns: $ncols\n");
  if ($ncols == 0)
    print ("Note: statement has no result set\n");
  for ($i = 0; $i < $ncols; $i++)
  {
    $col_info = $sth->getColumnMeta ($i);
    $flags = implode (",", array_values ($col_info["flags"]));
    printf ("--- Column %d (%s) ---\n", $i, $col_info["name"]);
    printf ("pdo_type:          %d\n", $col_info["pdo_type"]);
    printf ("native_type:       %s\n", $col_info["native_type"]);
    printf ("len:               %d\n", $col_info["len"]);
    printf ("precision:         %d\n", $col_info["precision"]);
    printf ("flags:             %s\n", $flags);
    printf ("table:             %s\n", $col_info["table"]);
  }
#@ _DISPLAY_METADATA_
}
catch (PDOException $e)
{
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
