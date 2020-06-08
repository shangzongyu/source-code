
all: dbm1 dbm2 lock1 lock2 lock3 lock4 lock5 memory1 memory2 memory3 memory4 memory5a memory5b memory6

INCLUDE=/usr/include/gdbm
LIBS=-lgdbm
# On some systems, you may have to change the line above to include the
# compatability library, as shown below. Note that the compatability library
# may have to come first.
# LIBS=-lgdbm_compat -lgdbm

# You make also need to edit the files dbm1.c and dbm2.c to change the
# include of  <ndbm.h> to be <gdbm-ndbm.h>


dbm1: dbm1.c
	gcc -I$(INCLUDE) $< -o $@ $(LIBS)

dbm2: dbm2.c
	gcc -I$(INCLUDE) $< -o $@ $(LIBS)


clean:
	rm -f dbm1 dbm2 lock1 lock2 lock3 lock4 lock5 memory1 memory2 memory3 memory4 memory5a memory5b memory6


