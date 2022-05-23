// Connect.java: connect to the MySQL server

import java.sql.*;

public class Connect
{
  public static void main (String[] args)
  {
    Connection conn = null;
    String url = "jdbc:mysql://localhost/cookbook";
    String userName = "cbuser";
    String password = "cbpass";

    try
    {
      conn = DriverManager.getConnection (url, userName, password);
      System.out.println ("Connected");
    }
    catch (Exception e)
    {
      System.err.println ("Cannot connect to server");
      System.exit (1);
    }
    if (conn != null)
    {
      try
      {
        conn.close ();
        System.out.println ("Disconnected");
      }
      catch (Exception e) { /* ignore close errors */ }
    }
  }
}
