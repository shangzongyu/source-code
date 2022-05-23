<?php
#@ _HEAD_
# Cookbook_Session.php: MySQL-based session storage module

require_once "Cookbook.php";
#@ _HEAD_

# Define handler routines

#@ _OPEN_
function mysql_sess_open ($save_path, $sess_name)
{
global $mysql_sess_dbh;

  # open connection to MySQL if it's not already open
  if ($mysql_sess_dbh === NULL)
  {
    try
    {
      $mysql_sess_dbh = Cookbook::connect ();
    }
    catch (PDOException $e)
    {
      $mysql_sess_dbh = NULL;
      return (FALSE);
    }
  }
  return (TRUE);
}
#@ _OPEN_

#@ _CLOSE_
function mysql_sess_close ()
{
global $mysql_sess_dbh;

  if ($mysql_sess_dbh !== NULL)    # close connection if it's open
    $mysql_sess_dbh = NULL;
  return (TRUE);
}
#@ _CLOSE_

#@ _READ_
function mysql_sess_read ($sess_id)
{
global $mysql_sess_dbh;

  try
  {
    $stmt = "SELECT data FROM php_session WHERE id = ?";
    $sth = $mysql_sess_dbh->prepare ($stmt);
    $sth->execute (array ($sess_id));
    list ($data) = $sth->fetch (PDO::FETCH_NUM);
    if (isset ($data))
      return ($data);
  }
  catch (PDOException $e) { /* do nothing */ }
  return ("");
}
#@ _READ_

#@ _WRITE_
function mysql_sess_write ($sess_id, $sess_data)
{
global $mysql_sess_dbh;

  try
  {
    $stmt = "REPLACE php_session (id, data) VALUES(?,?)";
    $sth = $mysql_sess_dbh->prepare ($stmt);
    $sth->execute (array ($sess_id, $sess_data));
    return (TRUE);
  }
  catch (PDOException $e)
  {
    return (FALSE);
  }
}
#@ _WRITE_

#@ _DESTROY_
function mysql_sess_destroy ($sess_id)
{
global $mysql_sess_dbh;

  try
  {
    $stmt = "DELETE FROM php_session WHERE id = ?";
    $sth = $mysql_sess_dbh->prepare ($stmt);
    $sth->execute (array ($sess_id));
    return (TRUE);
  }
  catch (PDOException $e)
  {
    return (FALSE);
  }
}
#@ _DESTROY_

#@ _GC_
function mysql_sess_gc ($sess_maxlife)
{
global $mysql_sess_dbh;

  try
  {
    $stmt = "DELETE FROM php_session
             WHERE update_time < NOW() - INTERVAL ? SECOND";
    $sth = $mysql_sess_dbh->prepare ($stmt);
    $sth->execute (array ($sess_maxlife));
  }
  catch (PDOException $e) { /* do nothing */ }
  return (TRUE);  # ignore errors
}
#@ _GC_

#@ _TAIL_
# Initialize the connection identifier, select user-defined
# session handling, and register the handler routines

$mysql_sess_dbh = NULL;
ini_set ("session.save_handler", "user");
session_set_save_handler (
  "mysql_sess_open",
  "mysql_sess_close",
  "mysql_sess_read",
  "mysql_sess_write",
  "mysql_sess_destroy",
  "mysql_sess_gc"
);
#@ _TAIL_
?>
