#
# Makefile for Java top-level.
#
DIRS=dbc
DEST=-d .

define common
	for i in $(DIRS) ;\
	do \
	    (cd $$i; [ -f Makefile ] && ( $(MAKE) $@ || exit 1)) || true;\
	done
endef

all:
	javac $(DEST) *.java
	$(common)

clean:
	rm -f *.class *~
	rm -f com/pragprog/util/*.class
	rm -f com/pragprog/sample/*.class
	$(common)

test:
	java junit.textui.TestRunner JUnitExample
	./test_driver
	$(common)
