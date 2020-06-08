# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 10

DEBUG=debug1 debug2 debug3 debug4
CINFO=cinfo assert
MEMORY=efence checker

CFLAGS=-g
LDFLAGS=-g

ALL= $(DEBUG) $(CINFO) $(MEMORY)

all: $(ALL)

cinfo.o: cinfo.c
	cc -c $(CFLAGS) -DDEBUG cinfo.c

assert: assert.o
	cc -o assert $(LDFLAGS) assert.o -lm

efence: efence.o
	cc -o efence $(LDFLAGS) efence.o -lefence

clean:
	@rm -f $(ALL) *~ *.o
