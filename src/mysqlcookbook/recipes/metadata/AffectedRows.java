// AffectedRows.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class AffectedRows
{
  public static void main (String[] args)
  {
    Connection conn = null;
    String stmt = "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'";

    try
    {
      conn = Cookbook.connect ();

      {
      try
      {
//#@ _FRAG1_
        Statement s = conn.createStatement ();
        int count = s.executeUpdate (stmt);
        s.close ();
        System.out.println ("Number of rows affected: " + count);
//#@ _FRAG1_
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
      }
      }

      {
      try
      {
//#@ _FRAG2_
        Statement s = conn.createStatement ();
        if (!s.execute (stmt))
        {
          // there is no result set, print the row count
          System.out.println ("Number of rows affected: " + s.getUpdateCount ());
        }
        s.close ();
//#@ _FRAG2_
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
      }
      }

    }
    catch (Exception e)
    {
      System.err.println ("Cannot connect to server");
    }
    finally
    {
      if (conn != null)
      {
        try
        {
          conn.close ();
        }
        catch (Exception e) { /* catch and ignore */ }
      }
    }
  }
}
