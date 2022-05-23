// EscapeColumnName.java

// Use the Java regex class to escape '%' and '_' // in column names
// (requires Java 1.4 or higher)

// #@ _IMPORT_
import java.util.regex.*;
// #@ _IMPORT_

public class EscapeColumnName
{
  public static void main (String[] args)
  {
// #@ _COMPILE_PATTERN_
    Pattern p = Pattern.compile("([_%])"); 
// #@ _COMPILE_PATTERN_

    if (args.length == 0)
    {
      System.out.println ("Specify column names on the command line");
      System.exit (0);
    }

    for (int i = 0; i < args.length; i++)
    {
      String origName = args[i];
      String name = args[i];
// #@ _ESCAPE_NAME_
      Matcher m = p.matcher(name);
      name = m.replaceAll ("\\\\$1");
// #@ _ESCAPE_NAME_
      System.out.println (origName + " -> " + name);
    }
  }
}
