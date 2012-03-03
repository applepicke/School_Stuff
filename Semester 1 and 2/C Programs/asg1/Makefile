### Standard CST8204 Makefile

# defaults
CC     = gcc
LD     = gcc
BACKUP = bak

# standard flags for $(CC) and $(LD)
CF = -ansi -pedantic -Wextra -Wall -O2
LF = -O2

# remove ### to enable debug
###DEBUG = -O0 -g

# file lists
H_FILES = numbers.h operators.h functions.h
O_FILES = calc.o input.o output.o shared.o
E_FILE  = calc

# create executable
$(E_FILE):	$(O_FILES)
		$(LD) $(LF) $(DEBUG) -o $(E_FILE) $(O_FILES)

# one pair of statements for each file in $(O_FILE)
calc.o:	calc.c $(H_FILES)
		$(CC) $(CF) $(DEBUG) -c calc.c
input.o: input.c $(H_FILES)
		$(CC) $(CF) $(DEBUG) -c input.c
output.o: output.c $(H_FILES)
		$(CC) $(CF) $(DEBUG) -c output.c
shared.o: shared.c $(H_FILES)
		$(CC) $(CF) $(DEBUG) -c shared.c

# standard housekeeping
# clean out all .o files
clean:
		rm -f $(O_FILES)
# copy all files to backup directory
backup:
		if [ ! -d $(BACKUP) ]; then mkdir $(BACKUP); fi
		cp *.h *.c Makefile $(BACKUP)
