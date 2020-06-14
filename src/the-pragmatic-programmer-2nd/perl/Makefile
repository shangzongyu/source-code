#
# From "Text Manipulation" et al,
# Makefile for the Perl directory 
#

all:		etest

test:		all
		@./etest
		@-mkdir testdir 2>/dev/null || true
		@touch testdir/lower
		@touch testdir/Mixed
		@touch testdir/UPPER
		@touch testdir/UPP123.ER
		@( cd testdir; perl ../lowercase.pl )
		@[ "$$(ls -m testdir)" = "Mixed, lower, upp123.er, upper" ]
		@rm -rf testdir

clean:
		rm -f etest etest.h etest.c testdir *~ *.o

#
# Derived files
#

etest:		etest_main.o etest.o ../c/tests.o

etest.o:	etest.h
etest_main.o:	etest.h

#START:genetest
etest.c etest.h:  etest.inc enumerated.pl
		  perl enumerated.pl etest.inc
#END:genetest


