import java.sql.*;
import com.kitebird.mcb.Cookbook;

public class Stmt {
  public static void main(String[] args) {
    Connection conn = null;

    try {
      conn = Cookbook.connect();

      // for statements that don't return a result set
      System.out.println("without_result_set");
      try {
//#@ _WITHOUT_RESULT_SET_
        Statement s = conn.createStatement();
        int count = s.executeUpdate(
          "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'");
        s.close(); // close statement
        System.out.println("Number of rows updated: " + count);
//#@ _WITHOUT_RESULT_SET_
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }
      // for statements that do return a result set, known column
      // (assumes no NULL values in data)
      System.out.println("with_result_set_without_null_known_columns_index");
      try {
//#@ _WITH_RESULT_SET_WITHOUT_NULL_KNOWN_COLUMNS_INDEX_
        Statement s = conn.createStatement();
        s.executeQuery("SELECT id, name, cats FROM profile");
        ResultSet rs = s.getResultSet();
        int count = 0;
        while (rs.next()) // loop through rows of result set
        {
          int id = rs.getInt(1); // extract columns 1, 2, and 3
          String name = rs.getString(2);
          int cats = rs.getInt(3);
          System.out.println("id: " + id +
            ", name: " + name +
            ", cats: " + cats);
          ++count;
        }
        rs.close(); // close result set
        s.close(); // close statement
        System.out.println("Number of rows returned: " + count);
//#@ _WITH_RESULT_SET_WITHOUT_NULL_KNOWN_COLUMNS_INDEX_
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

      // for statements that do return a result set, known column
      // (assumes no NULL values in data)
      System.out.println("with_result_set_without_null_known_columns_names");
      try {
        Statement s = conn.createStatement();
        s.executeQuery("SELECT id, name, cats FROM profile");
        ResultSet rs = s.getResultSet();
        int count = 0;
//#@ _WITH_RESULT_SET_WITHOUT_NULL_KNOWN_COLUMNS_NAMES_
        while (rs.next()) // loop through rows of result set
        {
          int id = rs.getInt("id");
          String name = rs.getString("name");
          int cats = rs.getInt("cats");
          System.out.println("id: " + id +
            ", name: " + name +
            ", cats: " + cats);
          ++count;
        }
//#@ _WITH_RESULT_SET_WITHOUT_NULL_KNOWN_COLUMNS_NAMES_
        rs.close(); // close result set
        s.close(); // close statement
        System.out.println("Number of rows returned: " + count);
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

      // for statements that do return a result set, known column
      // (assumes no NULL values in data)
      try {
        System.out.println("retrieve_as_strings");
        Statement s = conn.createStatement();
        s.executeQuery("SELECT id, name, cats FROM profile");
        ResultSet rs = s.getResultSet();
        int count = 0;
        while (rs.next()) // loop through rows of result set
        {
          {
//#@ _RETRIEVE_AS_STRINGS_
            String id = rs.getString("id");
            String name = rs.getString("name");
            String cats = rs.getString("cats");
            System.out.println("id: " + id +
              ", name: " + name +
              ", cats: " + cats);
//#@ _RETRIEVE_AS_STRINGS_
          } {
//#@ _RETRIEVE_AS_OBJECTS_
            Object id = rs.getObject("id");
            Object name = rs.getObject("name");
            Object cats = rs.getObject("cats");
            System.out.println("id: " + id.toString() +
              ", name: " + name.toString() +
              ", cats: " + cats.toString());
//#@ _RETRIEVE_AS_OBJECTS_
          }
          ++count;
        }
        rs.close(); // close result set
        s.close(); // close statement
        System.out.println("Number of rows returned: " + count);
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

      // for statements that do return a result set
      // (assumes no NULL values in data)
      System.out.println("with_result_set_without_null_unknown_columns");
      try {
        Statement s = conn.createStatement();
        s.executeQuery("SELECT * FROM profile");
//#@ _RESULT_SET_COLUMN_COUNT_
        ResultSet rs = s.getResultSet();
        ResultSetMetaData md = rs.getMetaData(); // get result set metadata
        int ncols = md.getColumnCount(); // get column count from metadata
//#@ _RESULT_SET_COLUMN_COUNT_
        int count = 0;
        while (rs.next()) // loop through rows of result set
        {
          for (int i = 0; i < ncols; i++) // loop through columns
          {
            String val = rs.getString(i + 1);
            if (i > 0)
              System.out.print(", ");
            System.out.print(val);
          }
          System.out.println();
          ++count;
        }
        rs.close(); // close result set
        s.close(); // close statement
        System.out.println("Number of rows returned: " + count);
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

      // for statements that do return a result set
      // (permits NULL values in data)
      System.out.println("with_result_set_with_null_unknown_columns");
      try {
//#@ _WITH_RESULT_SET_WITH_NULL_UNKNOWN_COLUMNS_
        Statement s = conn.createStatement();
        s.executeQuery("SELECT id, name, cats FROM profile");
        ResultSet rs = s.getResultSet();
        ResultSetMetaData md = rs.getMetaData();
        int ncols = md.getColumnCount();
        int count = 0;
        while (rs.next()) // loop through rows of result set
        {
          for (int i = 0; i < ncols; i++) // loop through columns
          {
            Object val = rs.getObject(i + 1);
            if (i > 0)
              System.out.print(", ");
            if (rs.wasNull())
              System.out.print("NULL");
            else
              System.out.print(val.toString());
          }
          System.out.println();
          ++count;
        }
        rs.close(); // close result set
        s.close(); // close statement
        System.out.println("Number of rows returned: " + count);
//#@ _WITH_RESULT_SET_WITH_NULL_UNKNOWN_COLUMNS_
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

      // what to do if you don't know the type of statement
      System.out.println("result_set_unknown");
      String stmtStr = "SHOW DATABASES";
      try {
//#@ _RESULT_SET_UNKNOWN_
        Statement s = conn.createStatement();
        if (s.execute(stmtStr)) {
          // there is a result set
          ResultSet rs = s.getResultSet();

          // ... process result set here ...

          rs.close(); // close result set
        } else {
          // there is no result set, just print the row count
          System.out.println("Number of rows affected: " + s.getUpdateCount());
        }
        s.close(); // close statement
//#@ _RESULT_SET_UNKNOWN_
      } catch (Exception e) {
        Cookbook.printErrorMessage(e);
      }

    } catch (Exception e) {
      System.err.println("Cannot connect to server");
    } finally {
      if (conn != null) {
        try {
          conn.close();
        } catch (Exception e) {}
      }
    }
  }
}
