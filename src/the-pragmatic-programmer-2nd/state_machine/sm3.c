/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/*************************************************************************
 *   sm3.c		* Implement word counter using a table
 *************************************************************************/

#include <ctype.h>
#include <stdio.h>

typedef enum {LT, GT, QT, WORD, OTHER } CHAR_TYPE;
typedef enum {S, W, CMD, STR } STATE;
typedef enum {NONE, INC } ACTION;

typedef struct {
  STATE  nextState;
  ACTION action;
} TRANSITION;

TRANSITION transitions[4][5] = {
/*          LT           GT          QT         WORD        OTHER  */
/* S */{{ CMD,NONE }, {S,  NONE}, {S,  NONE}, {W,  INC},  {S,  NONE}},
/* W */{{ CMD,NONE }, {S,  NONE}, {S,  NONE}, {W,  NONE}, {S,  NONE}},
/*CMD*/{{ CMD,NONE }, {S,  NONE}, {STR,NONE}, {CMD,NONE}, {CMD,NONE}},
/*STR*/{{ STR,NONE }, {STR,NONE}, {CMD,NONE}, {STR,NONE}, {STR,NONE}}
};

CHAR_TYPE chtype(int ch) {
  if (ch == '<') return LT;
  if (ch == '>') return GT;
  if (ch == '"') return QT;
  if (isalpha(ch)) return WORD;
  return OTHER;
}

int main(int argc, char **argv) {

  int   ch;
  int   count = 0;
  STATE state = S;

  while ((ch = getchar()) != EOF) {

    TRANSITION t = transitions[state][chtype(ch)];

    switch (t.action) {
    case NONE: break;
    case INC:  count++; break;
    default:   fprintf(stderr, "Invalid action %d\n", t.action);
    }
    state = t.nextState;
  }

  printf("Text contained %d word%s\n", 
	 count, count == 1 ? "" : "s");
  return 0;
}



