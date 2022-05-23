<?php
# placeholder.php: demonstrate statement processing in PHP
# (with placeholders)

# Note: This does't bother printing getCode() for errors because
# getMessage() includes the error code.

require_once "Cookbook.php";

try
{
  $dbh = Cookbook::connect ();
}
catch (PDOException $e)
{
  die ("Error message: " . $e->getMessage () . "\n");
}

# Prepare a statement, then pass the statement and data values to execute()

print ("Execute INSERT statement with prepare() + execute()\n");
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
$sth = $dbh->prepare ("INSERT INTO profile (name,birth,color,foods,cats)
                          VALUES(?,?,?,?,?)");
$sth->execute (array ("De'Mont","1973-01-12",NULL,"eggroll",4));
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
$count = $sth->rowCount ();
printf ("Number of rows inserted: %d\n", $count);

print ("Select rows using placeholder\n");
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_
$sth = $dbh->prepare ("SELECT * FROM profile WHERE cats > ?");
$sth->execute (array (2));
while ($row = $sth->fetch (PDO::FETCH_ASSOC))
{
  printf ("id: %s, name: %s, cats: %s\n",
          $row["id"], $row["name"], $row["cats"]);
}
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_

$dbh = NULL;
?>
