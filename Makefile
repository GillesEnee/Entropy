CC=gcc

COPT=-c -Wall -O3

ifdef DEBUG 
	COPT+= -g
endif

ID=$$("date -d '+%j:%R'")

SOBJ=element.o entropie.o matrice.o

all: Entropie

Entropie: ${SOBJ}
	${CC} -O3 -o $@ ${SOBJ} -lm

clean:
	@-rm -f *.o Entropie *~

svg: clean
	if (test -f 9.Archives/Entropie.tgz) then (rm -f 9.Archives/Entropie.tgz) fi
	tar -czf 9.Archives/Entropie.tgz *.c *.h Makefile

depend:
	@-makedepend -Y. *.c 2>/dev/null

doc: 
	cd 2.Doc && rm -rf *
	doxygen DoxyConf

.c.o:
	${CC} ${COPT} $<

# DO NOT DELETE

entropie.o: entropie.h matrice.h element.h
matrice.o: matrice.h element.h
