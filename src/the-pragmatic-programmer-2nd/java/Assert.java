/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package com.pragprog.util;

import java.lang.System;        // for exit()
import java.lang.Thread;        // for dumpStack()

public class Assert {

  /** Write a message, print a stack trace and exit if
    * our parameter is false.
    */
  public static void TEST(boolean condition) {
    if (!condition) {
      System.out.println("==== Assertion Failed ====");
      Thread.dumpStack();
      System.exit(1);
    }
  }

  // Testbed. If our argument is 'okay', try an assertion that
  // succeeds, if 'fail' try one that fails

  public static final void main(String args[]) {
    if (args[0].compareTo("okay") == 0) {
      TEST(1 == 1);
    }
    else if (args[0].compareTo("fail") == 0) {
      TEST(1 == 2);
    }
    else {
      throw new RuntimeException("Bad argument");
    }
  }
}


