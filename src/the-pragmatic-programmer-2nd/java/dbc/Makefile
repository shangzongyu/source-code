#
# Makefile for "Design by Contract" examples.
# This Makefile requires iContract version 0.3b1 or
# greater to compile.
#
# iContract.jar should be in your CLASSPATH.
#
# BASIC Existing classpath, including iContract
# SCODE is the sourcecode root
# CCODE is the root of the compiled code (uninstrumented, plain source)
# ISCODE is the root for the instrumented source code
# ICCODE is the root of the compiled instrumented code
# REP is the root for the repository tree (source and compiled __REP)

BASIC=$(JAVA_HOME)/lib/classes.zip:$(CLASSPATH)
ROOT=..
ISCODE=$(ROOT)/instr
REP=$(ROOT)/rep
SCODE=$(ROOT)
CCODE=$(ROOT)
ICCODE=$(ROOT)

all:
	@-mkdir -p $(REP)/dbc
	@-mkdir -p $(ISCODE)/dbc
	java -Djava.compiler=""  \
	-classpath $(CCODE):$(BASIC):$(REP) iContract.Tool  \
	-xdepend \
	-b"javac -g -d $(CCODE) -classpath $(CCODE):$(BASIC)" \
	-v -a \
	-c"javac -g -d $(ICCODE) -classpath $(CCODE):$(BASIC)"  \
	-o$(ISCODE)/@p/@f.@e  \
	-k$(REP)/@p  \
	-n"javac -classpath $(REP):$(BASIC)"  \
	-mpre,post,inv  \
	*.java

test:
	java dbc.dbc_list # Test list contract
	./test_blender.sh # Run regression test

clean:
	rm -fr *.class dbc *~ $(REP) $(ISCODE) depend


