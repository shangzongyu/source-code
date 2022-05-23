// Cmdline.java: demonstrate command-line option parsing in Java

import java.io.*;
import java.sql.*;
import gnu.getopt.*;  // need this for the Getopt class

public class Cmdline
{
//#@ _MAIN_
  public static void main (String[] args)
//#@ _MAIN_
  {
    Connection conn = null;
    String url = null;
    String hostName = null;
    String password = null;
    String userName = null;
    LongOpt[] longOpt = new LongOpt[3];
    int c;

    longOpt[0] =
      new LongOpt ("host", LongOpt.REQUIRED_ARGUMENT, null, 'h');
    longOpt[1] =
      new LongOpt ("password", LongOpt.REQUIRED_ARGUMENT, null, 'p');
    longOpt[2] =
      new LongOpt ("user", LongOpt.REQUIRED_ARGUMENT, null, 'u');

    // instantiate option-processing object, then
    // loop until there are no more options
    Getopt g = new Getopt ("Cmdline", args, "h:p:u:", longOpt);
    while ((c = g.getopt ()) != -1)
    {
      switch (c)
      {
      case 'h':
        hostName = g.getOptarg ();
        break;
      case 'p':
        password = g.getOptarg ();
        break;
      case 'u':
        userName = g.getOptarg ();
        break;
      case ':':       // a required argument is missing
      case '?':       // some other error occurred
        // no error message needed; getopt() prints its own
        System.exit (1);
      }
    }

    try
    {
      // construct URL, noting whether hostName was
      // given; if not, MySQL will assume localhost
      if (hostName == null)
        hostName = "";
      url = "jdbc:mysql://" + hostName + "/cookbook";
      conn = DriverManager.getConnection (url, userName, password);
      System.out.println ("Connected");
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
