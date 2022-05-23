<?php
# Cookbook.php: library file with utility method for connecting to MySQL
# using the PDO module

class Cookbook
{
  public static $host_name = "localhost";
  public static $db_name = "cookbook";
  public static $user_name = "cbuser";
  public static $password = "cbpass";

  # Establish a connection to the cookbook database, returning a database
  # handle.  Raise an exception if the connection cannot be established.
  # In addition, cause exceptions to be raised for errors.

  public static function connect ()
  {
    $dsn = "mysql:host=" . self::$host_name . ";dbname=" . self::$db_name;
    $dbh = new PDO ($dsn, self::$user_name, self::$password);
    $dbh->setAttribute (PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    return ($dbh);
  }

} # end Cookbook
?>
