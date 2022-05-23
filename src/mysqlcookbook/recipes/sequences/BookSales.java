// BookSales.java: show how to use LAST_INSERT_ID(expr)

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class BookSales
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();

      try
      {
//@# _UPDATE_COUNTER_
        Statement s = conn.createStatement ();
        s.executeUpdate (
            "INSERT INTO booksales (title,copies)"
            + "VALUES('The Greater Trumps',LAST_INSERT_ID(1))"
            + "ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1)",
            Statement.RETURN_GENERATED_KEYS);
        long count;
        ResultSet rs = s.getGeneratedKeys ();
        if (rs.next ())
        {
          count = rs.getLong (1);
        }
        else
        {
          throw new SQLException ("getGeneratedKeys() produced no value");
        }
        rs.close ();
        s.close ();
//@# _UPDATE_COUNTER_
        System.out.println ("count: " + count);
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
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
        catch (Exception e) { }
      }
    }
  }
}
