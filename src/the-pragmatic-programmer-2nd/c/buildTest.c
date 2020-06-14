/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "Code That's Easy to Test", some assertion examples.
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>


double epsilon = 0.0001;
#define mySqrt sqrt


#ifdef __TEST__
#endif /* spurious */

#if (1) 

void testValue(double num, double expected) {
  double result = mySqrt(num);
  if (num < 0) {
    // Should be NaN if negative arg
    assert(isnan(result));    
  }
  else {
    // Should be within tolerance otherwise
    assert(fabs(expected-result) < epsilon); 
  }
}

void someTests() {
  testValue(-4.0, 0.0);    // Basic tests
  testValue(0.0,  0.0);    
  testValue(64.0, 8.0);    
  testValue(ULONG_MAX, 65535.9999);
}

int main(int argc, char **argv) 
{
  argc--; argv++;       // skip program name

  if (argc < 2) {       // do standard tests if no args
    testValue(-4.0,  0.0);
    testValue( 0.0,  0.0);
    testValue( 2.0,  1.4142135624);
    testValue(64.0,  8.0);
    testValue(1.0e7, 3162.2776602);
  }
  else {                // else use args
    double num, expected;

    while (argc >= 2) {
      num = atof(argv[0]);
      expected = atof(argv[1]);
      testValue(num,expected);
      argc -= 2;
      argv += 2;
    }
  }
  return 0;
}
#endif
