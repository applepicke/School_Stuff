CFLAGS = -ansi -pedantic -Wextra -Wall -O2
SFLAGS = -O2


lab1: program.o handler.o
	gcc ${CFLAGS} -o lab1 program.o handler.o
program.o: program.c header.h
	gcc ${SFLAGS} -c program.c
handler.o: handler.c header.h
	gcc ${SFLAGS} -c handler.c

clean:
	rm -f *.o
