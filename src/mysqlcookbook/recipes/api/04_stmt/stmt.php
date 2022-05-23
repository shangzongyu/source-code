<?php
# stmt.php: demonstrate statement processing in PHP
# (without placeholders)

# Note: This does't bother printing getCode() for errors because
# getMessage() includes the error code.

require_once "Cookbook.php";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Cannot connect to server: " . $e->getMessage () . "\n");
}

# Default is same as PDO::FETCH_BOTH. Result can be used as ordered or
# associative array.

print ("Fetch using ordered array\n");
try
{
#@ _FETCHLOOP_1_
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
  $count = 0;
  while ($row = $sth->fetch (PDO::FETCH_NUM))
  {
    printf ("id: %s, name: %s, cats: %s\n", $row[0], $row[1], $row[2]);
    $count++;
  }
  printf ("Number of rows returned: %d\n", $count);
#@ _FETCHLOOP_1_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Fetch using associative array\n");
try
{
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
#@ _FETCHLOOP_2_
  while ($row = $sth->fetch (PDO::FETCH_ASSOC))
    printf ("id: %s, name: %s, cats: %s\n",
            $row["id"], $row["name"], $row["cats"]);
#@ _FETCHLOOP_2_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Fetch using object\n");
try
{
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
#@ _FETCHLOOP_3_
  while ($row = $sth->fetch (PDO::FETCH_OBJ))
    printf ("id: %s, name: %s, cats: %s\n", $row->id, $row->name, $row->cats);
#@ _FETCHLOOP_3_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Fetch after setting to database handle to associative fetch mode\n");
try
{
#@ _DBH_SET_FETCH_MODE_
  $dbh->setAttribute (PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
#@ _DBH_SET_FETCH_MODE_
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
  while ($row = $sth->fetch ())
    # Use print_r to make it more clear what the row structure is
    print_r ($row);
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Fetch after setting to statement handle to object fetch mode\n");
try
{
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
#@ _STH_SET_FETCH_MODE_
  $sth->setFetchMode (PDO::FETCH_OBJ);
#@ _STH_SET_FETCH_MODE_
  while ($row = $sth->fetch ())
    # Use print_r to make it more clear what the row structure is
    print_r ($row);
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Fetch rows using statement handle as iterator\n");
try
{
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
#@ _FETCH_ITERATOR_1_
  $sth->setFetchMode (PDO::FETCH_NUM);
  foreach ($sth as $row)
    printf ("id: %s, name: %s, cats: %s\n", $row[0], $row[1], $row[2]);
#@ _FETCH_ITERATOR_1_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

# Default is same as PDO::FETCH_BOTH. Result can be used as ordered or
# associative array.

print ("Fetch using fetchAll()\n");
try
{
  $sth = $dbh->query ("SELECT id, name, cats FROM profile");
#@ _FETCHALL_LOOP_
  $rows = $sth->fetchAll (PDO::FETCH_NUM);
  foreach ($rows as $row)
    printf ("id: %s, name: %s, cats: %s\n", $row[0], $row[1], $row[2]);
#@ _FETCHALL_LOOP_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

print ("Update rows\n");
try
{
#@ _UPDATE_
  $count = $dbh->exec ("UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'");
  printf ("Number of rows updated: %d\n", $count);
#@ _UPDATE_
}
catch (PDOException $e)
{
  print ("Oops, the statement failed\n");
  print ("Error message: " . $e->getMessage () . "\n");
}

$dbh = NULL;
?>
