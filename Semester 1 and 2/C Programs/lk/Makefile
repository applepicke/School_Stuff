FLAGS = -ansi -pedantic -Wextra -Wall -O2

lk: main.o check_file.o in_dir.o
	gcc ${FLAGS} -o lk main.o check_file.o in_dir.o -g
main.o: main.c
	gcc ${FLAGS} -c main.c -g
check_file.o: check_file.c
	gcc ${FLAGS} -c check_file.c -g
in_dir.o: in_dir.c
	gcc ${FLAGS} -c in_dir.c -g
clean:
	rm *.o
