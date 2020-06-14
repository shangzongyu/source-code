/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * Interface for our testbed.
  *
  * When we run tests on code, we want a consistent reporting of the results.
  * The tests.c file gives us he routine 'fail' which is used to
  * report a failed test.
  *
  **/

#ifndef _TESTS_H
#define _TESTS_H

void fail(const char *fmt, ...);

#endif
