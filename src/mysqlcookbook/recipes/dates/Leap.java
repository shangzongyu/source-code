public class Leap
{
  public static void main (String[] args)
  {
    // set up an array for test dates
    String[] date_array = {
                "1899-01-01",
                "1900-01-01",
                "1999-01-01",
                "2000-01-01",
                "1963-01-01",
                "1964-01-01"
              };
    for (int i = 0; i < date_array.length; i = i + 1)
    {
      String date = date_array[i];
//#@ _LEAP_TEST_
      int year = Integer.valueOf (date.substring (0, 4)).intValue ();
      boolean is_leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
//#@ _LEAP_TEST_
      System.out.println (date_array[i]
                          + " " + year
                          + " " + is_leap);
    }

  }
}
