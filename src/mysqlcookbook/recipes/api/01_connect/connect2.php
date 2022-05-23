<?php
# connect2.php: connect to the MySQL server, showing how to specify
# a port number or Unix domain socket path explicitly.

try
{
#@ _FRAG_PORT_
  $dsn = "mysql:host=127.0.0.1;database=cookbook;port=3307";
#@ _FRAG_PORT_
  $dbh = new PDO ($dsn, "cbuser", "cbpass");
  print ("Connected\n");
  $dbh = NULL;
  print ("Disconnected\n");
}
catch (PDOException $e)
{
  print ("Cannot connect to server\n");
}

try
{
#@ _FRAG_SOCKET_
  $dsn = "mysql:host=localhost;dbname=cookbook"
           . ";unix_socket=/var/tmp/mysql.sock";
#@ _FRAG_SOCKET_
  $dbh = new PDO ($dsn, "cbuser", "cbpass");
  print ("Connected\n");
  $dbh = NULL;
  print ("Disconnected\n");
}
catch (PDOException $e)
{
  print ("Cannot connect to server\n");
}
?>
