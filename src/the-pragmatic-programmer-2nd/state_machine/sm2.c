/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/*************************************************************************
 *   sm1.c		* Simple state machine
 *************************************************************************/

#include <ctype.h>
#include <stdio.h>

typedef enum { SPACE, WORD, END } STATE;

int main(int argc, char **argv) {

  STATE state = SPACE;
  int   ch;
  int   count = 0;

  while ((ch = getchar()) != EOF) {

    switch (state) {
      
    case SPACE:
      if (isalpha(ch)) {
	count++;
	state = WORD;
      }
      break;

    case WORD:
      if (!isalpha(ch))
	state = SPACE;
      break;

    default:
      fprintf(stderr, "Invalid state!\n");
    }
  }

  printf("Text contained %d word%s\n", 
	 count, count == 1 ? "" : "s");
}

