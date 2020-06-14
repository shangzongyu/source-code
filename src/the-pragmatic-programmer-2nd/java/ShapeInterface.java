/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
package com.pragprog.sample;

public class ShapeInterface { // for complilation
/**
  * From "Refactoring", the sample refactored version
  * of the code.
  */
public interface Geometry {    
    public double area();
}

public class Square implements Geometry {
  private double size;
  public Square(double new_size) {
    size=new_size;
  }
  public double area() {
    return size*size;
  }
}

public class Circle implements Geometry {
  private double radius;
  public Circle(double new_radius) {
    radius = new_radius;
  }
  public double area() {
    return Math.PI*radius*radius; // pi*r^2
  }
}

public class IrregularQuadrilateral implements Geometry {
  private double side1, side2, side3, side4;

  public IrregularQuadrilateral(double new_side1, double new_side2, 
                                double new_side3, double new_side4) {
    side1= new_side1;
    side2= new_side2;
    side3= new_side3;
    side4= new_side4;
  }
  public double area() {
    return side1 * side2 * side3 * side4;
  }
}


} // compilation wrapper

