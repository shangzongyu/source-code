/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "Algorithm Speed", here are implementations of
  * some common sorts.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "tests.h"

typedef unsigned long ELEMENT;

const int MAX_SIZE=10000000;
const int TEST_SIZE = 1000;

ELEMENT *array = 0;

ELEMENT *tmp_array;

#define SWAP(A,B) { ELEMENT tmp; tmp = A; A = B; B = tmp; }

/*
 * Prototype for a generic sort function
 */

typedef void (*SORT_FUNCTION)(ELEMENT *, int);

/*
 * Selection sort
 */

void selection(ELEMENT *input, int n) {
  int i, j;

  for (i = 0; i < n-1; i++) {
    int     lowest_index = i;
    ELEMENT lowest_value = input[i];

    for (j = i+1; j < n; j++)
      if (input[j] < lowest_value) {
	lowest_value = input[j];
	lowest_index = j;
      }

    SWAP(input[i], input[lowest_index]);
  }
}

/*
 * Bubble sort
 */

void bubble(ELEMENT *input, int n) {
  ELEMENT tmp;
  int i;

  do {
    
    tmp = input[0];

    for (i = 1; i < n; i++) {
      if (input[i-1] > input[i]) {
	tmp = input[i-1];
	input[i-1] = input[i];
	input[i] = tmp;
      }
    }
  } while (tmp != input[0]);
}


/*
 * insertion sort
 */

void insertion(ELEMENT *input, int n) {

  int i, j;
  ELEMENT tmp;

  for (i = 1; i < n; i++) {
    tmp = input[i];
    j = i;

    while ((j > 0) && (input[j-1] > tmp)) {
      input[j] = input[j-1];
      j--;
    }
    input[j] = tmp;
  }
}

/* quicksort
 */

int partition(ELEMENT *input, int first, int last) {
  ELEMENT pivot = input[first];
  int     right = last;
  int     left  = first+1;

  while (1) {

    while (input[right] > pivot) right--;
    while ((left < right) &&
	   input[left] <= pivot) left++;
    if (left >= right)
      break;
    SWAP(input[left], input[right]);
  }

  input[first] = input[right];
  input[right] = pivot;
  return right;
}

void quicksort(ELEMENT *input, int first, int last) {

  if (last > first) {
    int pivot_index = partition(input, first, last);
    quicksort(input, first, pivot_index-1);
    quicksort(input, pivot_index+1, last);
  }
}

void quick(ELEMENT *input, int count) {
  quicksort(input, 0, count-1);
}

/*
 * Shell sort
 */

void shell(ELEMENT *input, int n) {
  int      h = 1;
  ELEMENT  tmp;
  int      i, j;

  do { h = h*3+1; } while (h <= n);

  do {
    h = h/3;

    for (i = h; i < n; i++) {

      tmp = input[i];
      j = i;

      while (input[j-h]>tmp) {
	input[j] = input[j-h];
	j -= h;
	if (j < h)
	  break;
      }
      input[j] = tmp;
    }
  } while (h > 1);
}

/*
 * Straight radix sort - NOTE - only sorts unsigned
 */
void radix(ELEMENT *input, int n) {
  long count[256];

  int shift = 0;
  int i;

  while (shift < 32) {
    memset(count, 0, sizeof(count));

    for (i = 0; i < n; i++) {
      int bits = (input[i] >> shift) & 255;
      count[bits]++;
    }

    for (i = 1; i < 256; i++)
      count[i] += count[i-1];

    for (i = n-1; i >= 0; i--) {
      int bits = (input[i] >> shift) & 255;
      tmp_array[count[bits]] = input[i];
      count[bits]--;
    }

    memcpy(input, tmp_array, n*sizeof(input[0]));

    shift += 8;
  }
}

/*
 * Check the array is sorted, exit (1) if not
 */

void checkSorted(ELEMENT *array, int size, const char *type, const char *msg) {
  int i;

  for (i = 1; i < size; i++) {
    if (array[i-1] > array[i]) {
      fail("%s: failed on test '%s'", type, msg);
      exit(1);
    }
  }
}

/*
 * testSort - run the sort function and test we're doing it right
 */

void testSort(SORT_FUNCTION fn, const char *name) {

  int j;

  /* initialize the array with random numbers */
  for (j = 0; j < TEST_SIZE; j++)
    array[j] = random();

  (*fn)(array, TEST_SIZE);
  checkSorted(array, TEST_SIZE, name, "random fill");

  /* initialize the array with identical numbers */
  for (j = 0; j < TEST_SIZE; j++)
    array[j] = 0;

  (*fn)(array, TEST_SIZE);
  checkSorted(array, TEST_SIZE, name, "zeroes");

  /* initialize the array with ascending values */
  for (j = 0; j < TEST_SIZE; j++)
    array[j] = j;

  (*fn)(array, TEST_SIZE);
  checkSorted(array, TEST_SIZE, name, "ascending");

  /* initialize the array with descending values */
  for (j = 0; j < TEST_SIZE; j++)
    array[j] = TEST_SIZE - j;

  (*fn)(array, TEST_SIZE);
  checkSorted(array, TEST_SIZE, name, "descending");
}

/*
 * runSort - run each sort with increasing array sizes
 */

void runSort(SORT_FUNCTION fn, const char *name, 
	     int min, int max, int step, int test) {

  int howBig;

  /* make sure we start the same each time */
  srandom(1);

  if (test) {
    testSort(fn, name);
  }
  else {

    howBig = min;
    
    do {
      int j;
      struct timeval start, end;
      double diff;
      
      /* initialize the array of numbers to sort */
      for (j = 0; j < howBig; j++)
	array[j] = random();
      
      gettimeofday(&start, 0);
      
      (*fn)(array, howBig);
      
      gettimeofday(&end, 0);
      
      diff = (end.tv_sec - start.tv_sec) + 
	(double)(end.tv_usec-start.tv_usec)/1e6;
      
      printf("%-10s %8d  %g\n", name, howBig, diff);
      
      howBig += step;
      
    } while (howBig <= max);
  }
}

/*
 * Invoked with:
 *
 *    ./sort [-t] [name ...]
 *
 * where 'name' is one or more sort types. If '-t' is given, then
 * the sorts are tested instead of timed
 *
 */

int main(int argc, char **argv) {

  int testFlag = 0;
  long arraySize = MAX_SIZE;

  argc--; argv++;

  if (argc && (strcmp(*argv, "-t") == 0)) {
    argc--;
    argv++;
    testFlag++;
    arraySize = TEST_SIZE;
  }

  /*
   * For efficiency, pre-allocate our array
   */

  array = (ELEMENT *)malloc(arraySize*sizeof(array[0]));

  if (array == 0) {
    fprintf(stderr, "No memory for array\n");
    exit(1);
  }

  /*
   * Run them sorts
   */
  while (argc--) {

    if (strcmp(*argv, "radix") == 0) {
      tmp_array = (ELEMENT *)malloc(arraySize*sizeof(array[0]));
      runSort(radix, "radix", 1000000, MAX_SIZE, 1000000, testFlag);
      free(tmp_array);
    }
    else if (strcmp(*argv, "quick") == 0)
      runSort(quick, "quick", 1000000, MAX_SIZE, 1000000, testFlag);
    else if (strcmp(*argv, "selection") == 0)
      runSort(selection, "selection", 10000, 100000, 10000, testFlag);
    else if (strcmp(*argv, "shell") == 0)
      runSort(shell, "shell", 10000, MAX_SIZE, 10000, testFlag);
    else if (strcmp(*argv, "insertion") == 0)
      runSort(insertion, "insertion", 10000, 100000, 100000, testFlag);
    else if (strcmp(*argv, "bubble") == 0)
      runSort(bubble, "bubble", 10000, 100000, 100000, testFlag);
    else 
      fprintf(stderr, "Unknown sort type '%s'\n", *argv);

    argv++;
  }

  exit(0);
}
