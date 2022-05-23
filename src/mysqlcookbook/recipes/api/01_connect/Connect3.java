// Connect3.java: connect to the MySQL server, using a URL that
// specifies an explicit port number

import java.sql.*;

public class Connect3
{
  public static void main (String[] args)
  {
    Connection conn = null;
//#@ _FRAG_
    String url = "jdbc:mysql://127.0.0.1:3307/cookbook";
//#@ _FRAG_
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
