# $Id: Makefile,v 1.4 2012-11-09 12:22:45-08 - - $

JAVASRC    = jxref.java visitor.java messages.java options.java \
             queue.java counted_queue.java treemap.java
SOURCES    = ${JAVASRC} Makefile README
ALLSOURCES = ${SOURCES} pxref.perl
MAINCLASS  = jxref
CLASSES    = ${JAVASRC:%.java=%.class}
INNCLASSES = ${CLASSES:%.class=%\\$$*.class}
LS_INNER   = `(ls ${INNCLASSES} 2>/dev/null || true)`
JARCLASSES = ${CLASSES} ${LS_INNER}
JARFILE    = jxref
LISTING    = ../asg3j-jxref.code.ps
SUBMITDIR  = cmps012b-wm.f12 asg3

all : ${JARFILE}
	- checksource ${SOURCES}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	chmod +x ${JARFILE}
	- rm Manifest

%.class : %.java
	cid + $<
	javac -Xlint $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${ALLSOURCES}
	cid + ${ALLSOURCES}

lis : ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES}

submit : ${ALLSOURCES}
	submit ${SUBMITDIR} ${ALLSOURCES}

again : ${ALLSOURCES}
	make --no-print-directory spotless ci all lis

