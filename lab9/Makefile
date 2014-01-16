
MKFILE      = Makefile
SUBMAKE     = ${MAKE} --no-print-directory

GCC         = gcc -g -O0 -Wall -Wextra -std=gnu99

CHEADER     = inssort.h
CSOURCE     = numsort.c linesort.c ${CHEADER:.h=.c}
NUMOBJECTS  = numsort.o inssort.o
LINEOBJECTS = linesort.o inssort.o
OBJECTS     = ${CSOURCE:.c=.o}
EXECBIN1    = numsort
EXECBIN2    = linesort
SOURCES     = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTING     = lab9c-voidstar-generic.ps
SUBMITDIR   = cmps012b-wm.f12 lab9

all : ${EXECBIN1} ${EXECBIN2}

${EXECBIN1} : ${NUMOBJECTS}
	${GCC} -o $@ ${NUMOBJECTS}

${EXECBIN2} : ${LINEOBJECTS}
	${GCC} -o $@ ${LINEOBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core

spotless : clean
	- rm ${EXECBIN}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again :
	${MAKE} --no-print-directory spotless deps ci all lis


