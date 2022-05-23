// Connect2.java: connect to the MySQL server, using a URL that
// includes the username and password

import java.sql.*;

public class Connect2
{
  public static void main (String[] args)
  {
//#@ _FRAG_
    // connect using username and password included in URL
    Connection conn = null;
    String url = "jdbc:mysql://localhost/cookbook?user=cbuser&password=cbpass";

    try
    {
      conn = DriverManager.getConnection (url);
      System.out.println ("Connected");
    }
//#@ _FRAG_
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
