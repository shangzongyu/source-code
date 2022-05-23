<?php
# null-in-result.php: print undef values as "NULL"

require_once "Cookbook.php";

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
#@ _FETCHLOOP_1_
  $sth = $dbh->query ("SELECT name, birth, foods FROM profile");
  while ($row = $sth->fetch (PDO::FETCH_NUM))
  {
    foreach (array_keys ($row) as $key)
    {
      if ($row[$key] === NULL)
        $row[$key] = "NULL";
    }
    print ("name: $row[0], birth: $row[1], foods: $row[2]\n");
  }
#@ _FETCHLOOP_1_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
