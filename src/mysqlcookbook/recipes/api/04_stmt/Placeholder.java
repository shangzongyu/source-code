import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class Placeholder
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();

      // Statement with placeholder
      // - Use PreparedStatement, not Statement
      // - Use prepareStatement(), not createStatement()

      // insert record using placeholders
      try
      {
//#@ _EXECUTEUPDATE_
        PreparedStatement s;
        s = conn.prepareStatement (
                    "INSERT INTO profile (name,birth,color,foods,cats)"
                    + " VALUES(?,?,?,?,?)");
        s.setString (1, "De'Mont");         // bind values to placeholders
        s.setString (2, "1973-01-12");
        s.setNull (3, java.sql.Types.CHAR);
        s.setString (4, "eggroll");
        s.setInt (5, 4);
        s.close ();   // close statement
//#@ _EXECUTEUPDATE_
      }
      catch (Exception e)
      {
        Cookbook.printErrorMessage (e);
      }

      // retrieve records using placeholders
      {
//#@ _EXECUTEQUERY_
      PreparedStatement s;
      s = conn.prepareStatement ("SELECT * FROM profile WHERE cats > ?");
      s.setInt (1, 2);  // bind 2 to first placeholder
      s.executeQuery ();
      // ... process result set here ...
      s.close ();     // close statement
//#@ _EXECUTEQUERY_
      }
    }
    catch (Exception e)
    {
      Cookbook.printErrorMessage (e);
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
