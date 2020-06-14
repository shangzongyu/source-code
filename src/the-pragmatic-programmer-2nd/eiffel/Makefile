#
# This Makefile requires SmallEiffel version -0.79 or newer
# (note that version numbers increase towards 0.0)
#

COMPILE=$(SmallEiffel)/bin/compile
CLEAN=$(SmallEiffel)/bin/clean

TARGET=root.e
PROG=dbc_test

all:
	$(COMPILE) $(TARGET) -all_check -o $(PROG)

clean:
	rm -f $(PROG) *~
	$(CLEAN) $(TARGET)

test:
	$(PROG)
