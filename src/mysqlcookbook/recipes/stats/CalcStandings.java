/*
 * CalcStandings.java: calculate team standings, displaying each of the
 * four groups of records from the standings2 table separately.
 */

import java.text.*;     // for formatting
import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class CalcStandings
{
  public static void main (String[] args)
  {
    Connection conn = null;

    try
    {
      conn = Cookbook.connect ();

      // Compute best wins-losses value for each half season,
      // each division

      Statement s = conn.createStatement ();
      s.executeUpdate (
          "CREATE TEMPORARY TABLE firstplace"
          + " SELECT half, division, MAX(wins-losses) AS wl_diff"
          + " FROM standings2"
          + " GROUP BY half, division"
      );

      // Compute standings for each half season, division, with leader
      // GB displayed as "-"

      s.executeQuery (
          "SELECT st.half, st.division, st.team, st.wins AS W, st.losses AS L,"
          + " TRUNCATE(st.wins/(st.wins+st.losses),3) AS PCT,"
          + " IF(fp.wl_diff = st.wins-st.losses,"
          + "    '-',TRUNCATE((fp.wl_diff - (st.wins-st.losses)) / 2,1)) AS GB"
          + " FROM standings2 AS st, firstplace AS fp"
          + " WHERE st.half = fp.half AND st.division = fp.division"
          + " ORDER BY st.half, st.division, st.wins-st.losses DESC, PCT DESC"
      );
      ResultSet rs = s.getResultSet ();
      String curHalf = "";
      String curDiv = "";
      NumberFormat wlFmt = new DecimalFormat ("  ###");
      NumberFormat pctFmt = new DecimalFormat (" #.000");
      while (rs.next ())  // loop through rows of result set
      {
        String half = rs.getString ("half");
        String div = rs.getString ("division");
        String team = rs.getString ("team");
        int wins = rs.getInt ("W");
        int losses = rs.getInt ("L");
        double pct = rs.getDouble ("PCT");
        String gb = rs.getString ("GB");

        // new group of standings?
        if (!curDiv.equals (div) || !curHalf.equals (half))
        {
          // print standings header and remember new
          // half/division values
          System.out.println ();
          System.out.println (div
                              + " Division, season half "
                              + half);
          System.out.println (
              "Team                     W     L    PCT  GB"
          );
          curDiv = div;
          curHalf = half;
        }
        System.out.print (team);
        for (int i = team.length (); i < 20; i++)
          System.out.print (' ');
        System.out.print ("  " + wlFmt.format (wins));
        System.out.print ("  " + wlFmt.format (losses));
        System.out.print ("  " + pctFmt.format (pct));
        System.out.print ("  " + gb);
        System.out.println ();
      }
      rs.close ();  // close result set

      s.close ();   // close statement
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
