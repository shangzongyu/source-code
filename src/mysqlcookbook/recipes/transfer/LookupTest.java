// LookupTest.java: Demonstrate use of HashMap for lookup/validation purposes.

import java.util.HashMap;
import java.util.Iterator;

public class LookupTest
{
  public static void main (String[] args)
  {
    HashMap members = new HashMap ();

    // add some elements to the map, using values as keys
    members.put ((Object) "pig", null);
    members.put ((Object) "cat", null);
    members.put ((Object) "duck", null);
    members.put ((Object) "dog", null);

    // show the list of legal values

    System.out.print ("Legal values:");
    Iterator iter = members.keySet ().iterator ();
    while (iter.hasNext ())
    {
      System.out.print (" " + (String) iter.next ());
    }
    System.out.println ();

    // test some values to see whether they're in the lookup map

    System.out.println ("Test some values:");
    System.out.println ("cat ("
            + (members.containsKey ((Object) "cat") ? "good" : "bad")
            + ")");
    System.out.println ("snake ("
            + (members.containsKey ((Object) "snake") ? "good" : "bad")
            + ")");
  }
}
