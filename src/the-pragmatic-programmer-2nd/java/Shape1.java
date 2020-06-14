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
  * From "Refactoring", the sample refactored version
  * of the code.
  */
public abstract class Shape1 {
  public class Shape {
    
    private double size;
    
    public Shape(double size) {
      this.size = size;
    }
    
    public double getSize() { return size; }

    public abstract double area();
  }
  
  public class Square extends Shape {
    public Square(double size) {
      super(size);
    }
    
    public double area() {
      double size = getSize();
      return size*size;
    }
  }
  
  public class Circle extends Shape {
    public Circle(double size) {
      super(size);
    }
    
    public double area() {
      double size = getSize();
      return Math.PI*size*size/4.0;
    }
  }
}


