/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/** 
  * This file contains a number of different c examples, none of which
  * is large enough to warrant it's own file.  
  */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <math.h>

#include "tests.h"


extern char *optarg;
int exitcode = 0;

/**
 * This redefinition of 'exit' is a nasty little hack for testing purposes
 */

#define exit(n) exitcode = n

#define CHECK(LINE, EXPECTED)               \
  { int rc = LINE;                          \
    if (rc != EXPECTED)                     \
        ut_abort(__FILE__, __LINE__, #LINE,  rc, EXPECTED); }


void ut_abort(char *file, int ln, char *line, int rc, int exp) {
  fprintf(stderr, "%s line %d\n'%s': expected %d, got %d\n", 
                  file, ln, line, exp, rc);
  exit(1);
}

#undef exit

/************************************************************************
 * From algorithm_speed.tip
 ***********************************************************************/

typedef struct node Node;
struct node {
  Node *left;
  Node *right;
};

void getNodeAsString(const Node *node, char *buffer) {}

void printTree(const Node *node) {
  char buffer[1000];
  
  if (node) {
    printTree(node->left);
    
    getNodeAsString(node, buffer);
    puts(buffer);

    printTree(node->right);
  }
}

void printTree2(const Node *node) {
  char buffer[1000];
  
  while (node) {
    if (node->left) printTree(node->left);
    
    getNodeAsString(node, buffer);
    puts(buffer);
    
    node = node->right;
  }
}


void printTreePrivate(const Node *node, char *buffer) {
  if (node) {
    printTreePrivate(node->left, buffer);
    
    getNodeAsString(node, buffer);
    puts(buffer);

    printTreePrivate(node->right, buffer);
  }
}

void newPrintTree(const Node *node) {
  char buffer[1000];

  printTreePrivate(node, buffer);
}


/************************************************************************
 * From algorithm_speed.tip
 ***********************************************************************/

void linsearch() {
  int result;
  int n = 0;
  int i;
  int value = 0;
  int array[1];

  array[0] = 0;

  /* look for 'value' in 'array', returning either
   * an index or -1 if not found
   */
  
  result = -1;

  for (i = 0; i < n; i++) {
    if (array[i] == value) {
      result = i;
      break;
    }
  }
}

/* Truncate string to its last maxlen chars */

void string_tail(char *string, int maxlen) {
  int len = strlen(string);
  if (len > maxlen) {
    strcpy(string, string + (len - maxlen));
  }
}

/************************************************************************
 * From concurrency.tip
 ************************************************************************/


void bad_strtok() {
char buf1[BUFSIZ];
char buf2[BUFSIZ];
char *p, *q;

strcpy(buf1, "this is a test");
strcpy(buf2, "this ain't gonna work");

p = strtok(buf1, " ");
q = strtok(buf2, " ");
while (p && q) {
  printf("%s %s\n", p, q);
  p = strtok(NULL, " ");
  q = strtok(NULL, " ");
}
}

 /***********************************************************************/
void usage() {
  fprintf(stderr,"Usage: \n");
  fprintf(stderr,"       string_tail: -c maxlen -s string -t -e expected\n");
  fprintf(stderr,"       CHECK: -C\n");
  exit(1);
}


/**
  * Test harness for this code
  */
int main(int argc, char **argv)
{
  int c;
  int count = 10;  
  char *string = "TEST";
  char *expected = "???";
  struct stat statBuf;

  while ((c = getopt(argc, argv, "tc:s:e:Ca:b:")) != EOF) {
    switch(c) {

      /* String_tail tests */

    case 'c':  /* Get count */
      count = atoi(optarg);
      break;

    case 'e':
      expected = optarg;
      break;

    case 's':  /* Get string */
      string = optarg;
      break;

    case 't':  /* Run Truncate */
      string_tail(string, count);
      if (strcmp(string, expected) != 0) 
      fail("string_tail: expected %s got %s", expected, string);
      exit(0);
      break;

      /* CHECK tests */
      /* nasty hack to stop it exiting */

    case 'C':
      /* this one succeeds */
      CHECK(stat("/tmp", &statBuf), 0);
      if (exitcode != 0) fail("CHECK(/tmp) returned non-zero");

      fprintf(stderr,
    "Expect the message 'stat(\"/tmpxx\", &statBuf)': expected 0, got -1'\n");
      CHECK(stat("/tmpxx", &statBuf), 0);
      if (exitcode != 1) fail("CHECK(/tmpxx) expected 1, got %d", exitcode);
      exit(0);
      break;

    default:
      usage();
      exit(1);
    }
  }
  usage();
  exit(1);
}


