// APIMeta.java

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class APIMeta
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e) { /* catch and ignore */ }


    try
    {
//#@ _FRAG_
      DatabaseMetaData md = conn.getMetaData ();
      System.out.println ("Driver name: " + md.getDriverName ());
      System.out.println ("Driver version: " + md.getDriverVersion ());
//#@ _FRAG_
    }
    catch (Exception e)
    {
      System.out.println ("Error accessing metadata");
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
