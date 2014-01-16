# $Id$

JAVASRC    = exit255.java
MAINCLASS  = exit255
JARFILE    = exit255
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES}
SUBMITDIR  = cmps012b-wm.f12 lab2
FILE       = 0

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	javac $<

test: exit255
	exit255 2>255.output ; echo $$? >>255.output

submit :
	submit ${SUBMITDIR} ${FILE}
