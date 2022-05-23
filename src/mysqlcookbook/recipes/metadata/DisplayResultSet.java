// DisplayResultSet.java: display a result set in boxed form using
// result set metadata to determine column widths

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class DisplayResultSet
{
  public static void main (String[] args)
  {
    Connection conn = null;
    String stmt;

    if (args.length != 1)
    {
      System.err.println ("You must specify the statement as this"
                + " program's argument");
      System.exit (1);
    }
    stmt = args[0];

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }

    try
    {
//#@ _FRAG_
      System.out.println ("Statement: " + stmt);
      Statement s = conn.createStatement ();
      s.executeQuery (stmt);
      ResultSet rs = s.getResultSet ();
      displayResultSet (rs);
      rs.close ();
      s.close ();
//#@ _FRAG_
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

//#@ _DISPLAY_RESULT_SET_
  public static void displayResultSet (ResultSet rs) throws SQLException
  {
    ResultSetMetaData md = rs.getMetaData ();
    int ncols = md.getColumnCount ();
    int nrows = 0;
    int[] width = new int[ncols + 1];   // array to store column widths
    StringBuffer b = new StringBuffer (); // buffer to hold bar line

    // calculate column widths
    for (int i = 1; i <= ncols; i++)
    {
      // some drivers return -1 for getColumnDisplaySize();
      // if so, we'll override that with the column name length
      width[i] = md.getColumnDisplaySize (i);
      if (width[i] < md.getColumnName (i).length ())
        width[i] = md.getColumnName (i).length ();
      // isNullable() returns 1/0, not true/false
      if (width[i] < 4 && md.isNullable (i) != 0)
        width[i] = 4;
    }

    // construct +---+---...+ line
    b.append ("+");
    for (int i = 1; i <= ncols; i++)
    {
      for (int j = 0; j < width[i]; j++)
        b.append ("-");
      b.append ("+");
    }

    // print bar line, column headers, bar line
    System.out.println (b.toString ());
    System.out.print ("|");
    for (int i = 1; i <= ncols; i++)
    {
      System.out.print (md.getColumnName (i));
      for (int j = md.getColumnName (i).length (); j < width[i]; j++)
        System.out.print (" ");
      System.out.print ("|");
    }
    System.out.println ();
    System.out.println (b.toString ());

    // print contents of result set
    while (rs.next ())
    {
      ++nrows;
      System.out.print ("|");
      for (int i = 1; i <= ncols; i++)
      {
        String s = rs.getString (i);
        if (rs.wasNull ())
          s = "NULL";
        System.out.print (s);
        for (int j = s.length (); j < width[i]; j++)
          System.out.print (" ");
        System.out.print ("|");
      }
      System.out.println ();
    }
    // print bar line, and row count
    System.out.println (b.toString ());
    System.out.println ("Number of rows selected: " + nrows);
  }
//#@ _DISPLAY_RESULT_SET_
}
