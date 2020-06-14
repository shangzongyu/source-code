/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package com.pragprog.util;

import java.io.*;
import java.util.Enumeration;
import java.util.Vector;
import java.util.StringTokenizer;
import java.awt.*;
import java.awt.event.*;
import com.pragprog.util.Assert;

/**
  * This file contains a number of small Java examples that
  * didn't warrant their own classes.
  */

public class Misc {

  FileInputStream ipstream;

  public void open_passwd() throws FileNotFoundException {

    // This may throw FileNotFoundException...
    ipstream = new FileInputStream("/etc/passwd");
    
    // ...
  }

  public boolean open_user_file(String name) 
    throws FileNotFoundException {
    
    File f = new File(name);
    
    if (!f.exists()) {
      return false;
    }
    
    ipstream = new FileInputStream(f);
    return true;
  }

  public static void loopinv() {
    int arr[] = new int[10];

    int m = arr[0];   // example assumes arr.length > 0
    int i = 1;
    
    // Loop invariant: m = max(arr[0:i-1])
    while (i < arr.length) {
      m = Math.max(m, arr[i]);
      i = i + 1;
    }
  }

  public static void debug(String s) throws IOException {
    FileWriter fw = new FileWriter("debug.log", true);
    fw.write(s);
    fw.flush();
    fw.close();
  }

  public void testListener() {
    Button b = new Button("Sample");
    b.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        System.err.println ("Got button press");
      }
    });
  }

  public void testStringTokenizer() {
    StringTokenizer st1 = new StringTokenizer("this is a test");
    StringTokenizer st2 = new StringTokenizer("this test will work");

    while (st1.hasMoreTokens() && st2.hasMoreTokens()) {
      System.out.println(st1.nextToken());
      System.out.println(st2.nextToken());
    }
  }

  //
  // From Law of Demeter.
  //

  // 
  // Some dummy definitions so the examples will compile...
  //
  public class Money {
    public String printFormat() { return "$0.00"; }
  }

  public class BankAccount {
    public void printBalance() {};
    public Money getBalance() {
      return null;
    }
  }

  public void printToScreen(String s) {};

  public void showBalance(BankAccount acct) {
    Money amt = acct.getBalance();
    printToScreen(amt.printFormat());
  }

  public class Other {
  void showBalance(BankAccount b) {
    b.printBalance();
  }
  }

  //
  // Dummy definitions for the Colada example.
  //
  public class Blender {
    public void addIngredients(Enumeration e) {};
  }

  public class Colada {
    private Blender myBlender;
    private Vector myStuff;

    public Colada() {
      myBlender = new Blender();
      myStuff = new Vector();
    }
    private void doSomething() {
      myBlender.addIngredients(myStuff.elements());
    }
  }

  //
  // A test harness.
  //
  public final static void main(String args[]) {
    try {
      debug("A test string\n");
    } catch (Exception e) {
      System.out.println("Exception caught: " + e.getMessage());
    }
  }
}

