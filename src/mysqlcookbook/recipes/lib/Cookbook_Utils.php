<?php
# Cookbook_Utils.php: MySQL Cookbook utilities

# Quote an identifier by doubling internal backticks and adding
# a backtick at the beginning and end.

#@ _QUOTE_IDENTIFIER_
function quote_identifier ($ident)
{
  return ('`' . str_replace('`', '``', $ident) . '`');
}
#@ _QUOTE_IDENTIFIER_

# Given database and table names, return an array containing the
# names of the table's columns, in table definition order.

#@ _GET_COLUMN_NAMES_
function get_column_names ($dbh, $db_name, $tbl_name)
{
  $stmt = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS
           WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?
           ORDER BY ORDINAL_POSITION";
  $sth = $dbh->prepare ($stmt);
  $sth->execute (array ($db_name, $tbl_name));
  return ($sth->fetchAll (PDO::FETCH_COLUMN, 0));
}
#@ _GET_COLUMN_NAMES_

# Given database and table names, return information about the table columns.
# Return value is an array keyed by column name. Each array element is
# an array keyed by name of column in the INFORMATION_SCHEMA.COLUMNS table.

#@ _GET_COLUMN_INFO_
function get_column_info ($dbh, $db_name, $tbl_name)
{
  $stmt = "SELECT * FROM INFORMATION_SCHEMA.COLUMNS
           WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?";
  $sth = $dbh->prepare ($stmt);
  $sth->execute (array ($db_name, $tbl_name));
  $col_info = array();
  while ($row = $sth->fetch (PDO::FETCH_ASSOC))
    $col_info[$row["COLUMN_NAME"]] = $row;
  return ($col_info);
}
#@ _GET_COLUMN_INFO_

# get_enumorset_info() - get metadata for an ENUM or SET column.
# Take a datbase handle and database, table, and column names.
# Return an associative array keyed by "name", "type", "values", "nullable",
# and "default". Return FALSE if no info available.

#@ _GET_ENUMORSET_INFO_
function get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name)
{
  $stmt = "SELECT COLUMN_NAME, COLUMN_TYPE, IS_NULLABLE, COLUMN_DEFAULT
           FROM INFORMATION_SCHEMA.COLUMNS
           WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?";
  $sth = $dbh->prepare ($stmt);
  $sth->execute (array ($db_name, $tbl_name, $col_name));
  if (!($row = $sth->fetch (PDO::FETCH_NUM)))
    return (FALSE); # no such column
  $info = array ("name" => $row[0]);
  if (!preg_match ("/^(ENUM|SET)\((.*)\)$/i", $row[1], $match))
    return (FALSE); # not ENUM or SET
  $info["type"] = $match[1];
  # split value list at commas
  $info["values"] = explode (",", $match[2]);
  # remove surrounding quotes from values
  $info["values"] = preg_replace ("/^'(.*)'$/", "$1", $info["values"]);
  # determine whether column can contain NULL values
  $info["nullable"] = (strtoupper ($row[2]) == "YES");
  # get default value (unset value represents NULL)
  $info["default"] = $row[3];
  return ($info);
}
#@ _GET_ENUMORSET_INFO_

#@ _CHECK_ENUM_VALUE_
function check_enum_value ($dbh, $db_name, $tbl_name, $col_name, $val)
{
  $valid = 0;
  $info = get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name);
  if ($info && strtoupper ($info["type"]) == "ENUM")
  {
    # use case-insensitive comparison because default collation
    # (latin1_swedish_ci) is case-insensitive (adjust if you use
    # a different collation)
    $val = strtoupper ($val);
    foreach ($info["values"] as $v)
    {
      if ($val == strtoupper ($v))
      {
        $valid = 1;
        break;
      }
    }
  }
  return ($valid);
}
#@ _CHECK_ENUM_VALUE_
?>
