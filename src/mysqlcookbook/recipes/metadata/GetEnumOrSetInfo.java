// GetEnumOrSetInfo.java: wrapper to demonstrate EnumOrSetInfo()
// utility class.

// Usage: java GetEnumOrSetInfo db_name tbl_name col_name

import java.util.*;
import java.lang.String;

import java.sql.*;
import com.kitebird.mcb.Cookbook;
import com.kitebird.mcb.EnumOrSetInfo;

public class GetEnumOrSetInfo
{
  public static void main (String[] args)
  {
    Connection conn = null;
    EnumOrSetInfo info = null;

    if (args.length < 3)
    {
      System.out.println ("Usage: GetEnumOrSetInfo db_name tbl_name col_name");
      System.exit (1);
    }
    String dbName = args[0];
    String tblName = args[1];
    String colName = args[2];

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e)
    {
      System.out.println ("Could not connect to database");
      Cookbook.printErrorMessage (e);
    }

    try
    {
      info = new EnumOrSetInfo (conn, dbName, tblName, colName);
    }
    catch (Exception e)
    {
      System.out.println ("No information available (not ENUM or SET)?");
      System.exit (1);
    }

    try
    {
      if (conn != null)
        conn.close ();
    }
    catch (Exception e) { /* catch and ignore */ }

    System.out.println ("Information for "
                        + dbName + "."
                        + tblName + "."
                        + colName + ":");

    System.out.println ("Name: " + info.getName ());
    System.out.println ("Type: " + info.getType ());
    System.out.print ("Legal values: ");
    List values = info.getValues ();
    for (int i = 0; i < values.size (); i++)
    {
      if (i > 0)
        System.out.print (",");
      System.out.print (values.get (i));
    }
    System.out.println ();
    System.out.println ("Nullable: " + (info.getNullable () ? "yes" : "no"));
    if (info.getDefault () == null)
      System.out.println ("default: NULL");
    else
      System.out.println ("default: " + info.getDefault ());
  }
}
