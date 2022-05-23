// GetDatabaseNames.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class GetDatabaseNames
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }

    try
    {
//#@ _FRAG_
      // get list of databases
      DatabaseMetaData md = conn.getMetaData ();
      ResultSet rs = md.getCatalogs ();
      while (rs.next ())
        System.out.println (rs.getString (1));  // column 1 = database name
      rs.close ();
//#@ _FRAG_
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
