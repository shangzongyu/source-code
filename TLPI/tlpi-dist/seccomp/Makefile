include ../Makefile.inc

GEN_EXE = 

LINUX_EXE = libseccomp_demo seccomp_control_open seccomp_deny_open seccomp_perf

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

libseccomp_demo : libseccomp_demo.c
	${CC} -o $@ libseccomp_demo.c ${CFLAGS} ${LDLIBS} -lseccomp

${EXE} : ${TLPI_LIB}		# True as a rough approximation
