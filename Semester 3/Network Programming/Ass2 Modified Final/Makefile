FLAGS = -ansi -pedantic -Wextra -Wall -O2

all: client server

server: server.o functions.o 
	gcc ${FLAGS} -o server server.o functions.o

server.o: server.c header.h
	gcc ${FLAGS} -c server.c
	
functions.o: functions.c header.h
	gcc ${FLAGS} -c functions.c

client: client.o
	gcc ${FLAGS} -o client client.o
	
client.o: client.c header.h
	gcc ${FLAGS} -c client.c
	
clean:
	rm *.o
	
