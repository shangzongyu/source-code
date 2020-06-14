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
  * From "Design by Contract", A 'heisenbug' is a bug due to effects
  * suggested by the Heisenburg Uncertainty Principle; i.e., the act
  * of observation can affect the test.  
  */

class dbc_heisenbug {

  /**
    * @pre anItem != null   // Require real data
    * @post pop() == anItem // Verify that it's
    *                       // on the stack
    */
  public void push(final String anItem) 
  {
  }

  public String pop() {
    return null;
  }

  public static void main(String args[]) {
      new dbc_heisenbug();
  }


}
