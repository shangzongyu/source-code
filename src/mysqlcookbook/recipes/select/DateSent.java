// DateSent.java: fetch rows, refer to columns by name

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class DateSent
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();

      try
      {
//#@ _FRAG_
        Statement s = conn.createStatement ();
        s.executeQuery ("SELECT srcuser,"
                        + " DATE_FORMAT(t,'%M %e, %Y') AS date_sent"
                        + " FROM mail");
        ResultSet rs = s.getResultSet ();
        while (rs.next ())  // loop through rows of result set
        {
          String name = rs.getString ("srcuser");
          String dateSent = rs.getString ("date_sent");
          System.out.println ("user: " + name + ", date sent: " + dateSent);
        }
        rs.close ();
        s.close ();
//#@ _FRAG_
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
