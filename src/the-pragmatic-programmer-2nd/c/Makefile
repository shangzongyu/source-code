#
# Makefile for c source examples
#
TARGETS=bad_balance balance misc refactor sort buildTest
CFLAGS=-Wall
LDFLAGS=-lm

all: $(TARGETS)

misc:	misc.o tests.o

sort:	sort.o tests.o

#
# Make will exit with error 1 if any of the
# grep's fail.
#
test: all
	@./buildTest 49.0 7.0
	@./buildTest -49.0 0.0
	@./misc -c 5 -s 01234567890   -e "67890"	      -t
	@./misc -c 15 -s 01234567890  -e "01234567890" -t
	@./misc -c 1 -s 01234567890   -e "0"           -t
	@./misc -c 0 -s 01234567890   -e ""            -t
	@./misc -c 100 -s 01234567890 -e "01234567890" -t
	@./misc -C
	@./sort -t quick selection radix shell insertion bubble

clean:
	rm -f *.o $(TARGETS) *~

