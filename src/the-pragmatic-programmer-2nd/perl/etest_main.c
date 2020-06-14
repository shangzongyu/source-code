/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * Testbed for enumerated.pl
  *
  * Check that the output of enumerated.pl agrees with test.inc
  *
  */

#include <string.h>

#include "../c/tests.h"
#include "etest.h"

#define TRY(T) if (strcmp(ETEST_name[T], #T)) fail(#T "'s name is wrong")


int main() {
  TRY(STATEA);
  TRY(STATEB);
  TRY(STATEC);
  TRY(STATED);

  return 0;
}

