/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package dbc;

/**
  * From "Design by Contract", this code is for the exercises.
  */

/**
  * @invariant getSpeed() > 0
  *        implies isFull()              // Don't run empty
  *
  * @invariant getSpeed() >= 0 &&
  *        getSpeed() < 10               // Range check
  */

class dbc_ex {

  private int mySpeed = 0;
  private boolean myIsFull = false;


  /**
    * Return the speed, 0 (off) through 10
    */
  public int getSpeed() {
    return mySpeed;
  }

  /**
    * @pre Math.abs(getSpeed() - x) <= 1 // Only change by one
    * @pre x >= 0 && x < 10              // Range check
    * @post getSpeed() == x              // Honor requested speed
    */
  public void setSpeed(final int x)

  {
    mySpeed = x;
  }


  boolean isFull() {
    return myIsFull;
  }

  /**
    * @pre !isFull()                     // Don't fill it twice
    * @post isFull()                     // Ensure it was done
    */
  void fill()

  {
    myIsFull = true;
  }

  /**
    * @pre isFull()                      // Don't empty it twice
    * @post !isFull()                    // Ensure it was done
    */
  void empty()

  {
    myIsFull = false;
  }

  public static void main(String args[]) {

    // Create the blender to test
    dbc_ex blender = new dbc_ex();

    // And test it according to the string on standard input
    try {
      int a;
      char c;

      while ((a = System.in.read()) != -1) {

        c = (char)a;

        if (Character.isWhitespace(c)) {
          continue;
        }

        if (Character.isDigit(c)) {
          blender.setSpeed(Character.digit(c, 10));
        }
        else {
          switch (c) {
            case 'F': blender.fill();
                      break;
            case 'E': blender.empty();
                      break;
            case 's': System.out.println("SPEED: " +
                                         blender.getSpeed());
                      break;
            case 'f': System.out.println("FULL " +
                                         blender.isFull());
                      break;
            default: throw new RuntimeException(
                      "Unknown Test directive");
          }
        }
      }
    }
    catch (java.io.IOException e) {
      System.err.println("Test jig failed: " + e.getMessage());
    }

    System.err.println("Completed blending\n");
    System.exit(0);

  }

}
