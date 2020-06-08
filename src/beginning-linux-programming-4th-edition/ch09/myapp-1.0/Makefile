all: myapp

# Which compiler
CC = gcc

# Where to install
INSTDIR = /usr/local/bin
MANDIR = /usr/local/man/man1

# Where are include files kept
INCLUDE = .

# Options for development
CFLAGS = -g -Wall -ansi

# Options for release
# CFLAGS = -O -Wall -ansi

# Local Libraries
MYLIB = mylib.a

myapp: main.o $(MYLIB)
	$(CC) -o myapp main.o $(MYLIB)


$(MYLIB): $(MYLIB)(2.o) $(MYLIB)(3.o)
main.o: main.c a.h
2.o: 2.c a.h b.h
3.o: 3.c b.h c.h

clean:
	-rm -f main.o 2.o 3.o $(MYLIB) *~

install: myapp myapp.1
	@if [ -d $(INSTDIR) ]; \
	then \
		cp myapp $(INSTDIR);\
		chmod a+x $(INSTDIR)/myapp;\
		chmod og-w $(INSTDIR)/myapp;\
		echo "Installed in $(INSTDIR)";\
	else \
		echo "Sorry, $(INSTDIR) does not exist";\
	fi
	@if [ -d $(MANDIR) ]; \
	then \
		cp myapp.1 $(MANDIR);\
		gzip -f $(MANDIR)/myapp.1;\
		echo "Installed in $(MANDIR)";\
	else \
		echo "Sorry, $(MANDIR) does not exist";\
	fi

myapp-1.0.tar.gz: myapp myapp.1 myapp.spec
	-rm -rf myapp-1.0
	mkdir myapp-1.0
	cp *.c *.h *.1 Makefile myapp-1.0
	tar zcvf $@ myapp-1.0

myapp.rpm: myapp-1.0.tar.gz
	cp $< /usr/src/packages/SOURCES
	rpm -ba myapp.spec

