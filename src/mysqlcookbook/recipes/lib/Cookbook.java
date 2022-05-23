//#@ _PART_1_
// Cookbook.java: library file with utility methods for connecting to MySQL
// using MySQL Connector/J and for handling exceptions

//#@ _PACKAGE_
package com.kitebird.mcb;
//#@ _PACKAGE_

import java.sql.*;
//#@ _PART_1_
//#@ _IMPORT_JAVA_UTIL_
import java.util.*;   // need this for properties file support
//#@ _IMPORT_JAVA_UTIL_

//#@ _PART_2_
public class Cookbook
{
  // Establish a connection to the cookbook database, returning
  // a connection object.  Throw an exception if the connection
  // cannot be established.

  public static Connection connect () throws Exception
  {
    String url = "jdbc:mysql://localhost/cookbook";
    String user = "cbuser";
    String password = "cbpass";

    return (DriverManager.getConnection (url, user, password));
  }
//#@ _PART_2_

// This should add a message to the exception structure if the
// props file open fails?

//#@ _PROPS_CONNECT_
  // Establish a connection to the cookbook database, returning
  // a connection object.  Read parameters from a properties file.

  public static Connection propsConnect () throws Exception
  {
    String propsFile = "Cookbook.properties";
    Properties props = new Properties ();
    String host = "";
    String database = "";
    String user = "";
    String password = "";

    props.load (Cookbook.class.getResourceAsStream (propsFile));
    host = props.getProperty ("host", "localhost");
    database = props.getProperty ("database", "cookbook");
    user = props.getProperty ("user", "");
    password = props.getProperty ("password", "");

    String url = "jdbc:mysql://" + host + "/" + database;
    return (DriverManager.getConnection (url, user, password));
  }
//#@ _PROPS_CONNECT_

//#@ _PART_3_
  // Return an error message as a string

  public static String getErrorMessage (Exception e)
  {
    StringBuffer s = new StringBuffer ();
    if (e instanceof SQLException)  // JDBC-specific exception?
    {
      // print general message, plus any database-specific message
      s.append ("Error message: " + e.getMessage () + "\n");
      s.append ("Error code: " + ((SQLException) e).getErrorCode () + "\n");
    }
    else
    {
      s.append (e + "\n");
    }
    return (s.toString ());
  }

  // Get the error message and print it to System.err

  public static void printErrorMessage (Exception e)
  {
    System.err.println (Cookbook.getErrorMessage (e));
  }
}
//#@ _PART_3_
