// Harness.java: test harness for Cookbook library class

import java.sql.*;
//#@ _IMPORT_
import com.kitebird.mcb.Cookbook;
//#@ _IMPORT_

public class Harness
{
  public static void main (String[] args)
  {
    Connection conn = null;
    try
    {
      conn = Cookbook.connect ();
      System.out.println ("Connected");
    }
    catch (Exception e)
    {
      Cookbook.printErrorMessage (e);
      System.exit (1);
    }
    finally
    {
      if (conn != null)
      {
        try
        {
          conn.close ();
          System.out.println ("Disconnected");
        }
        catch (Exception e)
        {
          String err = Cookbook.getErrorMessage (e);
          System.out.println (err);
        }
      }
    }
  }
}
