// AddInsect.java: demonstrate client-side getLastInsertID() method
// for getting the most recent AUTO_INCREMENT value.

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class AddInsect
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();

      try
      {
//@# _WITH_STATEMENT_
        Statement s = conn.createStatement ();
        s.executeUpdate ("INSERT INTO insect (name,date,origin)"
                         + " VALUES('moth','2014-09-14','windowsill')",
                         Statement.RETURN_GENERATED_KEYS);
//@# _WITH_STATEMENT_
//@# _GETGENERATEDKEYS_
        long seq;
        ResultSet rs = s.getGeneratedKeys ();
        if (rs.next ())
        {
          seq = rs.getLong (1);
        }
        else
        {
          throw new SQLException ("getGeneratedKeys() produced no value");
        }
        rs.close ();
        s.close ();
//@# _GETGENERATEDKEYS_
        System.out.println ("seq: " + seq);
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
      }

      try
      {
//@# _WITH_PREPARED_STATEMENT_
        PreparedStatement s = conn.prepareStatement (
                            "INSERT INTO insect (name,date,origin)"
                            + " VALUES('moth','2014-09-14','windowsill')",
                            Statement.RETURN_GENERATED_KEYS);
        s.executeUpdate ();
//@# _WITH_PREPARED_STATEMENT_
        long seq;
        ResultSet rs = s.getGeneratedKeys ();
        if (rs.next ())
        {
          seq = rs.getLong (1);
        }
        else
        {
          throw new SQLException ("getGeneratedKeys() produced no value");
        }
        rs.close ();
        s.close ();
        System.out.println ("seq: " + seq);
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

