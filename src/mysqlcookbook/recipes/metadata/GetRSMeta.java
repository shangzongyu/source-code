// GetRSMeta.java: run a statement and display its result set metadata

// The program runs a default statement, which can be overridden by supplying
// a statement as an argument on the command line.

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class GetRSMeta
{
  public static void main (String[] args)
  {
    Connection conn = null;
    // #@ _DEFAULT_STATEMENT_
    String stmt = "SELECT name, birth FROM profile";
    // #@ _DEFAULT_STATEMENT_

    // override statement with command line argument if one was given
    if (args.length > 0)
      stmt = args[0];

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }

    try
    {
// #@ _DISPLAY_METADATA_
      System.out.println ("Statement: " + stmt);
      Statement s = conn.createStatement ();
      s.executeQuery (stmt);
      ResultSet rs = s.getResultSet ();
      ResultSetMetaData md = rs.getMetaData ();
      // metadata information becomes available at this point ...
      int ncols = md.getColumnCount ();
      System.out.println ("Number of columns: " + ncols);
      if (ncols == 0)
        System.out.println ("Note: statement has no result set");
      for (int i = 1; i <= ncols; i++)  // column index values are 1-based
      {
        System.out.println ("--- Column " + i
                  + " (" + md.getColumnName (i) + ") ---");
        System.out.println ("getColumnDisplaySize: " + md.getColumnDisplaySize (i));
        System.out.println ("getColumnLabel:       " + md.getColumnLabel (i));
        System.out.println ("getColumnType:        " + md.getColumnType (i));
        System.out.println ("getColumnTypeName:    " + md.getColumnTypeName (i));
        System.out.println ("getPrecision:         " + md.getPrecision (i));
        System.out.println ("getScale:             " + md.getScale (i));
        System.out.println ("getTableName:         " + md.getTableName (i));
        System.out.println ("isAutoIncrement:      " + md.isAutoIncrement (i));
        System.out.println ("isNullable:           " + md.isNullable (i));
        System.out.println ("isCaseSensitive:      " + md.isCaseSensitive (i));
        System.out.println ("isSigned:             " + md.isSigned (i));
      }
      rs.close ();
      s.close ();
// #@ _DISPLAY_METADATA_
    }
    catch (Exception e)
    {
      System.out.println ("An error occurred while processing the statement");
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
