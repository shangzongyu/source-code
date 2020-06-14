/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * Standard interface for tests.
  *
  * Provides the routine 'fail' to fail a test
  *
  */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#include "tests.h"

/*
 * Report a failed test and exit
 */

void fail(const char *fmt, ...) {

  va_list ap;
  
  va_start(ap, fmt);

  fprintf(stderr, "TEST FAILED -- ");
  vfprintf(stderr, fmt,  ap);
  fprintf(stderr, "\n");

  exit(1);
}

