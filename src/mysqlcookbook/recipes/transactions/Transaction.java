// Transaction.java: simple transaction demonstration

// By default, this creates an InnoDB table.  If you specify a storage
// engine on the command line, that will be used instead.  Normally,
// this should be a transaction-safe engine that is supported by your
// server.  However, you can pass a nontransactional storage engine
// to verify that rollback doesn't work properly for such engines.

// The script uses a table named "money" and drops it if necessary.
// Change the name if you have a valuable table with that name. :-)

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class Transaction
{

  // Create the example table and populate it with a couple of rows

  public static void init_table (Connection conn, String tbl_engine)
  {
    try
    {
      Statement s = conn.createStatement ();
      s.executeUpdate ("DROP TABLE IF EXISTS money");
      s.executeUpdate ("CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name))"
                      + " ENGINE = " + tbl_engine);
      s.executeUpdate ("INSERT INTO money (name, amt) VALUES('Eve', 10)");
      s.executeUpdate ("INSERT INTO money (name, amt) VALUES('Ida', 0)");
      s.close ();
    }
    catch (Exception e)
    {
      System.err.println ("Cannot initialize test table");
      Cookbook.printErrorMessage (e);
      System.exit (1);
    }
  }

  // Display the current contents of the example table

  public static void display_table (Connection conn)
  {
    try
    {
      Statement s = conn.createStatement ();
      s.executeQuery ("SELECT name, amt FROM money");
      ResultSet rs = s.getResultSet ();
      while (rs.next ())
      {
        String name = rs.getString (1);
        int amt = rs.getInt (2);
        System.out.println (name + " has $" + amt);
      }
      rs.close ();
      s.close ();
    }
    catch (Exception e)
    {
      System.err.println ("Cannot display contents of test table");
      Cookbook.printErrorMessage (e);
    }
  }

  public static void main (String[] args)
  {
    Connection conn = null;
    String tbl_engine = "InnoDB"; // default storage engine

    if (args.length > 0)
      tbl_engine = args[0];
    System.err.println ("Using storage engine " + tbl_engine
              + " to test transactions");

    try
    {
      conn = Cookbook.connect ();
    }
    catch (Exception e)
    {
      System.err.println ("Cannot connect to database");
      Cookbook.printErrorMessage (e);
      System.exit (1);
    }

    System.err.println ("----------");
    System.err.println ("This transaction should succeed.");
    System.err.println ("Table contents before transaction:");
    init_table (conn, tbl_engine);
    display_table (conn);

//#@ _DO_TRANSACTION_
    try
    {
      conn.setAutoCommit (false);
      Statement s = conn.createStatement ();
      // move some money from one person to the other
      s.executeUpdate ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
      s.executeUpdate ("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'");
      s.close ();
      conn.commit ();
      conn.setAutoCommit (true);
    }
    catch (SQLException e)
    {
      System.err.println ("Transaction failed, rolling back. Error was:");
      Cookbook.printErrorMessage (e);
      // empty exception handler in case rollback fails
      try
      {
        conn.rollback ();
        conn.setAutoCommit (true);
      }
      catch (Exception e2) { }
    }
//#@ _DO_TRANSACTION_
    // show final contents of table
    System.err.println ("Table contents after transaction:");
    display_table (conn);

    System.err.println ("----------");
    System.err.println ("This transaction should fail.");
    System.err.println ("Table contents before transaction:");
    init_table (conn, tbl_engine);
    display_table (conn);

    try
    {
      conn.setAutoCommit (false);
      Statement s = conn.createStatement ();
      // move some money from one person to the other
      s.executeUpdate ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
      s.executeUpdate ("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'");
      s.close ();
      conn.commit ();
      conn.setAutoCommit (true);
    }
    catch (SQLException e)
    {
      System.err.println ("Transaction failed, rolling back. Error was:");
      Cookbook.printErrorMessage (e);
      // empty exception handler in case rollback fails
      try
      {
        conn.rollback ();
        conn.setAutoCommit (true);
      }
      catch (Exception e2) { }
    }
    // show final contents of table
    System.err.println ("Table contents after transaction:");
    display_table (conn);

    try
    {
      conn.close ();
    }
    catch (Exception e) { }
  }
}
