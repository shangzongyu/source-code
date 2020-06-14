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
  * From "Design by Contract", examples of bad contracts.
  */

class dbc_bad {

  public class Node {
    public Node(String s) {}
    public Node next() { return this; }
    public Node prev() { return this; }
  }
  public static int max = 100;
  private int data[];
  /**
    * @post data[index-1] < data[index] &&
    *       data[index] == aValue
    */
  public Node insertNumber (final int aValue) 
  {
    int index = findPlaceToInsert(aValue);
    /*
    ...
  */
    return null;
  }

  private int findPlaceToInsert(final int aValue) {
    return 0;
  }

  public static void main(String args[]) {
      new dbc_bad();
  }

}
