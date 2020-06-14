/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "Code That's Easy to test",
  * this example requires JUnit 2.1 or greater.
  */

import java.util.Enumeration;
import java.util.Vector;
import junit.framework.*;

public class JUnitExample extends TestCase {
  
  
  public class DblPair {
    public double num;
    public double expected;
    public DblPair(double a, double b) {
      num = a;
      expected = b;
    }
    public double getNum() {
      return num;
    }
    public double getExpected() {
      return expected;
    }
  }

  private double mySqrt(final double x) { 
    if (x < 0) {
      throw new RuntimeException("Arg must be positive");
    }
    return Math.sqrt(x); 
  }
  protected Vector testData = new Vector();
  private static final double epsilon = 0.0001;

  public JUnitExample(final String name) {
    super(name);
  }

  protected void setUp() {
    // Load up test data...
    testData.addElement(new DblPair(-4.0,0.0));
    testData.addElement(new DblPair(0.0,0.0));
    testData.addElement(new DblPair(64.0,8.0));
    testData.addElement(new DblPair(Double.MAX_VALUE,
                                    1.3407807929942597E154));
  }

  public void testValue(double num, double expected) {
    double result = 0.0;

    try {                    // We may throw a
      result = mySqrt(num);  // precondition exception
    }
    catch (Throwable e) {
      if (num < 0.0)         // If input is < 0, then
        return;              // we're expecting the
      else                   // exception, otherwise
        assert(false);       // force a test failure
    }

    assert(Math.abs(expected-result) < epsilon*expected);
  }


  public void testMySqrt() {
    double num, expected, result = 0.0;

    Enumeration enum = testData.elements();
    while (enum.hasMoreElements()) {
      DblPair p = (DblPair)enum.nextElement();
      num       = p.getNum();
      expected  = p.getExpected();
      testValue(num, expected);
    }
  }

  public static Test suite() {
      TestSuite suite= new TestSuite();
      suite.addTest(new JUnitExample("testMySqrt"));
      return suite;
  }
}

