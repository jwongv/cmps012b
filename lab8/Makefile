
GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = l8stat.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = l8stat
LISTING  = ../lab8s-unixprog-stat.ps
SUBMIT   = submit cmps012b-wm.f12 lab8

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

