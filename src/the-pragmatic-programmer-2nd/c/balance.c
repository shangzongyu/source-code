/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "How to Balance Resources", illustrate better resource balancing.
  */

#include <stdio.h>

typedef struct {
  double balance;
} Customer;


void readCustomer(FILE *cFile, Customer *cRec) {
  fread(cRec, sizeof(*cRec), 1, cFile);
}

void writeCustomer(FILE *cFile, Customer *cRec) {
  rewind(cFile);
  fwrite(cRec, sizeof(*cRec), 1, cFile);
}

void updateCustomer(const char *fName, double newBalance) {
  FILE *cFile;
  Customer cRec;
  
  cFile = fopen(fName, "r+");        // >---
  readCustomer(cFile, &cRec);        //     |
  if (newBalance >= 0.0) {           //     |
    cRec.balance = newBalance;       //     |
    writeCustomer(cFile, &cRec);     //     |
  }                                  //     |
  fclose(cFile);                     // <---
}

int main(int argc, char **argv) {

  if (argc > 1) {
    updateCustomer(argv[1], -1.0);
    updateCustomer(argv[1], 0.0);
    updateCustomer(argv[1], 1.0);
  }
  else
    fprintf(stderr, "Missing file name\n");

  return 0;
}
