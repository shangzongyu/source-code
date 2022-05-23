/*
 * EnumOrSetInfo.java: Class to retrieve metadata for an ENUM or SET column.
 * Takes a database connection and database, table, and column names.
 *
 * Usage:
 * EnumOrSetInfo info = new EnumOrSetInfo (conn, dbName, tblName, colName);
 *
 * After getting the information object, the enumeration or set information
 * is exposed through a set of getter methods.
 */

package com.kitebird.mcb;

import java.util.*;
import java.util.regex.*;   // requires Java 1.4 or higher
import java.lang.String;
import java.sql.*;

public class EnumOrSetInfo
{
  String name;
  String type;
  String defVal;
  boolean nullable;
  List<String> values;

  /* constructor to set up column information */

  public EnumOrSetInfo (Connection conn,
                        String dbName,
                        String tblName,
                        String colName) throws Exception
  {

    PreparedStatement s = conn.prepareStatement (
          "SELECT COLUMN_NAME, COLUMN_TYPE, IS_NULLABLE, COLUMN_DEFAULT"
        + " FROM INFORMATION_SCHEMA.COLUMNS"
        + " WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?");
    s.setString (1, dbName);
    s.setString (2, tblName);
    s.setString (3, colName);
    s.executeQuery ();
    ResultSet rs = s.getResultSet ();
    if (!rs.next ())
    {
      rs.close ();
      s.close ();
      throw new Exception ("no information found");
    }

    name = rs.getString (1);
    type = rs.getString (2);
    nullable = rs.getString (3).toUpperCase().equals ("YES");
    defVal = rs.getString (4);
    if (rs.wasNull ())
      defVal = null;
    rs.close ();
    s.close ();

    // column must be an ENUM or SET
    Pattern pc = Pattern.compile ("(enum|set)\\((.*)\\)",
                                  Pattern.CASE_INSENSITIVE);
    Matcher m = pc.matcher (type);
    // matches() fails unless it matches entire string
    if (!m.matches ())
      throw new Exception ("column is not an ENUM or SET");

    type = m.group (1);  // reset to initial type word

    // split value list on commas, trim quotes from end of each word
    values = new ArrayList<String> ();
    String[] v = m.group (2).split (",");
    for (int i = 0; i < v.length; i++)
      values.add (v[i].substring (1, v[i].length() - 1));
  }

  /* getter methods to expose column information */

  public String getName ()
  {
    return (name);
  }

  public String getType ()
  {
    return (type);
  }

  public String getDefault ()
  {
    return (defVal);
  }

  public boolean getNullable ()
  {
    return (nullable);
  }

  public List getValues ()
  {
    return (values);
  }
}
