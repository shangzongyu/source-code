// SeqDemo.java: demonstrate AUTO_INCREMENT operations

import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class SeqDemo
{
  public static void initTable (Connection conn, String tblType)
  {
    try
    {
      Statement s = conn.createStatement ();
      s.execute ("DROP TABLE IF EXISTS seqdiag");
      s.execute (
            "CREATE TABLE seqdiag"
            + " (seq INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (seq))"
            + " ENGINE=" + tblType);
      s.close ();
// use SHOW CREATE TABLE here to see if type is correct
    }
    catch (Exception e)
    {
      Cookbook.printErrorMessage (e);
    }
  }

  public static void main (String[] args)
  {
    Connection conn = null;
    String tblType = "InnoDB";

    if (args.length > 0)
      tblType = args[0];
    System.out.println ("Testing using table type: " + tblType);

    try
    {
      conn = Cookbook.connect ();
      initTable (conn, tblType);

      // Check whether different Statement objects hold
      // independent insert-id values 

      String stmt = "INSERT INTO seqdiag (seq) VALUES(NULL)";
      Statement s = conn.createStatement ();
      Statement s2 = conn.createStatement ();
      ResultSet rs;
      s.executeUpdate (stmt, Statement.RETURN_GENERATED_KEYS);
      s2.executeUpdate (stmt, Statement.RETURN_GENERATED_KEYS);
      long seq;
      long seq2;
      rs = s.getGeneratedKeys ();
      if (rs.next ())
      {
        seq = rs.getLong (1);
      }
      else
      {
        throw new SQLException ("getGeneratedKeys() produced no value");
      }
      rs.close ();
      rs = s2.getGeneratedKeys ();
      if (rs.next ())
      {
        seq2 = rs.getLong (1);
      }
      else
      {
        throw new SQLException ("getGeneratedKeys() produced no value");
      }
      rs.close ();
      System.out.println ("seq1: " + seq + ", seq2: " + seq2);
      if (seq == seq2)
        System.out.println ("VALUES SHOULD HAVE BEEN DIFFERENT!");
      s.close ();
      s2.close ();
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
