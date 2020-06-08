# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 11

SYSTEM=system1 system2 pexec
FORK=fork1 wait fork2
FILTER=upper useupper
SIGNALS=ctrlc1 alarm ctrlc2

CFLAGS=-g
LDFLAGS=-g

ALL= $(SYSTEM) $(FORK) $(FILTER) $(SIGNALS)

all: $(ALL)

clean:
	@rm -f $(ALL) *~ *.o
