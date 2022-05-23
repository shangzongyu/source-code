import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class NullInResult
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();
      System.out.println ("Connected");

      // for queries that do return a result set
      // (permits NULL values in data)
      {
      try
      {
//#@ _FETCHLOOP_
        Statement s = conn.createStatement ();
        s.executeQuery ("SELECT name, birth, foods FROM profile");
        ResultSet rs = s.getResultSet ();
        ResultSetMetaData md = rs.getMetaData ();
        int ncols = md.getColumnCount ();
        while (rs.next ())  // loop through rows of result set
        {
          for (int i = 0; i < ncols; i++) // loop through columns
          {
            String val = rs.getString (i+1);
            if (i > 0)
              System.out.print (", ");
            if (rs.wasNull ())
              System.out.print ("NULL");
            else
              System.out.print (val);
          }
          System.out.println ();
        }
        rs.close ();  // close result set
        s.close ();   // close statement
//#@ _FETCHLOOP_
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
      }
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
          System.out.println ("Disconnected");
        }
        catch (Exception e) { }
      }
    }
  }
}
