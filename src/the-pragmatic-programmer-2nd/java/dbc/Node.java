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
  * From "Design by Contract",
  * Simple Node for the dbc list example.
  */

public class Node {

  /**********************************************************************/
  /* Private                                                            */
  /**********************************************************************/
  private Node myPrevious;
  private Node myNext;
  private String myValue;

  /**********************************************************************/
  /* Class Methods                                                      */
  /**********************************************************************/

  /**********************************************************************/
  /* Creation                                                           */
  /**********************************************************************/

  /**
    * Constructor.
    * @param aValue String value to store.
    */

  public Node (String aValue) {
    myValue = aValue;
  }

  /**********************************************************************/
  /* Command                                                            */
  /**********************************************************************/

  /**
    * Set the previous <code>Node</code>.
    */
  public void setPrev(Node aNode) {
    myPrevious = aNode;
  }

  /**
    * Set the next <code>Node</code>.
    */
  public void setNext(Node aNode) {
    myNext = aNode;
  }

  /**********************************************************************/
  /* Queries                                                            */
  /**********************************************************************/

  /**
    * Get the value of this <code>Node</code>.
    */
  public String value() {
    return myValue;
  }

  /**
    * Get the next <code>Node</code>.
    */
  public Node next() {
    return myNext;
  }

  /**
    * Get the previous <code>Node</code>.
    */
  public Node prev() {
    return myPrevious;
  }

  /** 
    * Return a string representation of this object.
    */
  public String toString() {
    StringBuffer ret = new StringBuffer();
    ret.append("(" + myPrevious.myValue + ")-> ");
    ret.append(myValue);
    ret.append(" ->(" + myNext.myValue + ")");
    return ret.toString();
  }

} // End class Node

