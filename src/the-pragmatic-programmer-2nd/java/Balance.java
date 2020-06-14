/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package com.pragprog.sample;

import java.io.*;

/**
  * From "How to Balance Resources", a simple example of try..catch.
  */

public class Balance {

  String tmpFileName = "tmpfile";

  /*****************************************************************/
  /* Constructors                                                  */
  /*****************************************************************/

  public Balance() throws IOException {
    doSomething();
  }

  /*****************************************************************/
  /* Command                                                       */
  /*****************************************************************/

  public void doSomething() throws IOException {

    File tmpFile = new File(tmpFileName);
    FileWriter tmp = new FileWriter(tmpFile);

    try {
      // do some work
    }
    finally {
      tmpFile.delete();
    }
  }

  /*****************************************************************/
  /* Queries                                                       */
  /*****************************************************************/

  /*****************************************************************/
  /* Property Access                                               */
  /*****************************************************************/

  public final static void main(String args[]) throws IOException {

    new Balance();
  }

}


