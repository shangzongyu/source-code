// This program demonstrates how to read a Java properties file to
// get MySQL connection parameters.

//#@ _FRAG_
import java.sql.*;
import java.util.*;   // need this for properties file support

public class ReadPropsFile
{
  public static void main (String[] args)
  {
    Connection conn = null;
    String url = null;
    String propsFile = "Cookbook.properties";
    Properties props = new Properties ();

    try
    {
      props.load (ReadPropsFile.class.getResourceAsStream (propsFile));
    }
    catch (Exception e)
    {
      System.err.println ("Cannot read properties file");
      System.exit (1);
    }
    try
    {
      // construct connection URL, encoding username
      // and password as parameters at the end
      url = "jdbc:mysql://"
            + props.getProperty ("host")
            + "/cookbook"
            + "?user=" + props.getProperty ("user")
            + "&password=" + props.getProperty ("password");
      conn = DriverManager.getConnection (url);
      System.out.println ("Connected");
    }
    catch (Exception e)
    {
      System.err.println ("Cannot connect to server");
    }
    finally
    {
      try
      {
        if (conn != null)
        {
          conn.close ();
          System.out.println ("Disconnected");
        }
      }
      catch (SQLException e) { /* ignore close errors */ }
    }
  }
}
//#@ _FRAG_
