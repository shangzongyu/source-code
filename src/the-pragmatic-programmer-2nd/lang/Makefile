#
# Makefile for "Domain Languages" code.
#
CFLAGS=-g

all:		turtle timeparser

turtle:		turtle.c

timeparser:	timeparser.c

timeparser.c:	timeparser.y
		bison -o timeparser.c timeparser.y

clean:
		rm -f a lex.yy.c y.tab.c y.tab.h *~ y.output turtle core
		rm -f timeparser

test:		test_turtle test_tp

test_turtle:	turtle
		@./turtle <turtle_tests > xxx 2>&1
		@diff xxx turtle_results || (echo "turtle test FAILED"; exit 1)
		@rm -f xxx

test_tp: 	timeparser
		perl ./test_tp.pl ./timeparser
		perl ./test_tp.pl ./timeparser.pl
