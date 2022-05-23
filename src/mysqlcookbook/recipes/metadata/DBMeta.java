// DBMeta.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class DBMeta
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }

//#@ _FRAG_
    try
    {
      DatabaseMetaData md = conn.getMetaData ();
      ResultSet rs;

      System.out.println ("Tables:");
      rs = md.getTables (conn.getSchema(), "", "%", null);
      while (rs.next ())
        System.out.println (rs.getString (3));

      System.out.println ("Columns in profile table and their types:");
      rs = md.getColumns (conn.getSchema(), "", "profile", "%");
      while (rs.next ())
        System.out.println (rs.getString (4) + ": " + rs.getString (6));
    }
    catch (Exception e)
    {
      System.out.println ("Error accessing database metadata");
      Cookbook.printErrorMessage (e);
    }

//#@ _FRAG_

    try
    {
      if (conn != null)
        conn.close ();
    }
    catch (Exception e) { /* catch and ignore */ }
  }
}
