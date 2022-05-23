// GetTableNames.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class GetTableNames
{
  public static void main (String[] args)
  {
    Connection conn = null;
    String dbName = "";
    if (args.length > 0)
      dbName = args[0];

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }

    try
    {
      // arguments:
      // 1 - catalog name (database name)
      // 2 - schema name (unused)
      // 3 - table name pattern.  "%" means "all"
      // 4 - table types; unused
      // result set columns are the same; the third column will be
      // a different table name in each row.
//#@ _FRAG_
      // get list of tables in database named by dbName
      DatabaseMetaData md = conn.getMetaData ();
      ResultSet rs = md.getTables (dbName, "", "%", null);
      while (rs.next ())
        System.out.println (rs.getString (3));  // column 3 = table name
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
