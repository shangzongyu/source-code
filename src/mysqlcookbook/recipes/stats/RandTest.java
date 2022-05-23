/*
 * RandTest.java: create a frequency distribution of RAND() values.
 * This provides a test of the randomness of RAND().
 */

/*
 * Method is to draw random numbers in the range from 0 to 1.0,
 * and count how many of them occur in .1-sized intervals (0 up
 * to .1, .1 up to .2, ..., .9 up *through* 1.0).
 */

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class RandTest
{
  public static void main (String[] args)
  {
    Connection conn = null;
    int nPicks = 1000;    // number of times to pick a number
    int[] bucket = new int[10];

    try
    {
      conn = Cookbook.connect ();
      Statement s = conn.createStatement ();

      for (int i = 0; i < nPicks; ++i)
      {
        s.executeQuery ("SELECT RAND()");
        ResultSet rs = s.getResultSet ();
        rs.next ();
        double val = rs.getDouble (1);
        rs.close ();
        int slot = (int) (val * 10);
        if (slot > 9)
          slot = 9;     // put 1.0 in last slot
        ++bucket[slot];
      }
      s.close ();

      // Print the resulting frequency distribution

      for (int slot = 0; slot < 10; ++slot)
      {
        System.out.println (slot+1 + " " + bucket[slot]);
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
