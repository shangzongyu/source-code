/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package dbc;

import java.util.Enumeration;
import java.util.Vector;

/**
  * From "Design by Contract", simple list insertion example.
  * This can be made a circular list by changing just a few lines.
  */


/**
  * @invariant forall Node n in elements() |
  *    n.prev() != null
  *      implies
  *         n.value().compareTo(n.prev().value()) > 0
  */

public class dbc_list {

  /**
    * @pre contains(aNode) == false
    * @post contains(aNode) == true
    */
  public void insertNode(final Node aNode) {
    // ...

    if (myFirst == null) {
      myFirst = aNode;
      myLast = aNode;
      aNode.setNext(null);
      aNode.setPrev(null);
    }
    else {
      myLast.setNext(aNode);
      aNode.setNext(null);
      aNode.setPrev(myLast);
      myLast = aNode;
     }
  }

  /**
    * Return the first node in the list
    */
  public Node first() {
    return myFirst;
  }

  /**
    * Return the last node in the list
    */
  public Node last() {
    return myLast;
  }

  /**
    * Does the list contain the given node?
    */
  public boolean contains(final Node aNode) {
    Node itr = myFirst;
    if (itr == null)
      return false;
    boolean result = false;
    while (true) {
      if (itr.value().equals(aNode.value())) {
        result = true;
        break;
      }
      if (itr == myLast) {
        break;
      }
      itr = itr.next();
    }
    return result;
  }

  /**
    * Return the list as an enumeration.
    */
  public Enumeration elements() {
    Vector v = new Vector();
    Node itr = myFirst;
    if (itr != null) {
      while (true) {
        v.addElement(itr);
        if (itr == myLast) {
          break;
        }
        itr = itr.next();
      }
    }
    return v.elements();
  }

  /**
    * Print out the list as a string.
    */
  public String toString() {
    StringBuffer ret = new StringBuffer();
    ret.append("\ndbc_list: First = " + myFirst.value() + 
                           " Last = " + myLast.value() + "\n");
    Node itr = myFirst;
    if (itr != null) {
      while (true) {
        ret.append("\t" + itr.toString() + "\n");
        if (itr == myLast) {
          break;
        }
        itr = itr.next();
      }
    }
    return ret.toString();
  }

  /**
    * Check an assertion (see also Assert)
    */
  public static void check(boolean aCondition) {
    if (!aCondition) {
      System.out.println("==== Assertion Failed ====");
      Thread.dumpStack();
      System.exit(1);
    }
  }

  private Node myFirst;
  private Node myLast;

  /**
    * Test the class.
    */
  public static void main(String[] args) { 
    dbc_list list = new dbc_list();
    Node a = new Node("TestA"); list.insertNode(a);
    Node b = new Node("TestB"); list.insertNode(b);
    Node c = new Node("TestC"); list.insertNode(c);
    check(a != b);
    check(b != c);
    check(a.next() == b);
    check(b.next() == c);
    check(c.prev() == b);
    check(b.prev() == a);
    System.err.println ("dbc_list passed.");
  }

}
