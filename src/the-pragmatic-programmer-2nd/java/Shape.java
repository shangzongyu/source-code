/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package com.pragprog.sample;

/**
  * From "Refactoring", the original shape example.
  */

public class Shape {
  
  public static final int SQUARE   = 1;
  public static final int CIRCLE   = 2;
  public static final int RIGHT_TRIANGLE = 3;
  
  private int    shapeType;
  private double size;
  
  public Shape(int shapeType, double size) {
    this.shapeType = shapeType;
    this.size      = size;
  }
  
  // ... other methods ...


  
  public double area() {
    switch (shapeType) {
    case SQUARE:   return size*size;
    case CIRCLE:   return Math.PI*size*size/4.0;
    case RIGHT_TRIANGLE: return size*size/2.0;
    }
    return 0;
  }
}


