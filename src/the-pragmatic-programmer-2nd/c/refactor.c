/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "Refactoring", exercise and answer.
  */


typedef enum {TEXAS, OHIO, MAINE } STATE;

double basis(int d) { return 0.0; }
double extra(int d) { return 0.0; }

void main() {
  STATE state;
  int TX_RATE = 1;
  int OH_RATE = 1;
  int ME_RATE = 1;
  
  int rate;
  int amt;
  double calc;
  int base = 1;
  int points;
  int rate_lookup[10];

  if (state == TEXAS) {
    rate = TX_RATE;
    amt  = base * TX_RATE;
    calc = 2*basis(amt) + extra(amt)*1.05;
  }
  else if ((state == OHIO) || (state == MAINE)) {
    rate = (state == OHIO) ? OH_RATE : ME_RATE;
    amt  = base * rate;
    calc = 2*basis(amt) + extra(amt)*1.05;
    if (state == OHIO)
      points = 2;
  }
  else {
    rate = 1;
    amt  = base;
    calc = 2*basis(amt) + extra(amt)*1.05;
  }

  rate = rate_lookup[state];
  
  amt  = base * rate;
  calc = 2*basis(amt) + extra(amt)*1.05;
  
  if (state == OHIO)
    points = 2;
}
