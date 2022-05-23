// ServerMeta.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class ServerMeta
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e)
    {
      Cookbook.printErrorMessage (e);
      System.exit (1);
    }

    try
    {
//#@ _FRAG_
      DatabaseMetaData md = conn.getMetaData ();
      // can also get this with SELECT VERSION()
      System.out.println ("Product version: " + md.getDatabaseProductVersion ());
      // this is similar to SELECT USER() but doesn't include the hostname
      System.out.println ("Username: " + md.getUserName ());
//#@ _FRAG_
      System.out.println ("Product name: " + md.getDatabaseProductName ());
      System.out.println ("Connection URL: " + md.getURL ());
    }
    catch (Exception e)
    {
      System.out.println ("Error accessing database metadata");
      Cookbook.printErrorMessage (e);
    }

    try
    {
      if (conn != null)
        conn.close ();
    }
    catch (Exception e) { /* catch and ignore */ }
  }
}
