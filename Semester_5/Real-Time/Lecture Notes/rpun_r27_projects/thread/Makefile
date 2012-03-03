
#
#	Makefile for thread project
#

DEBUG = -g
CC = qcc
LD = qcc

TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoppcbe

CFLAGS += $(DEBUG) $(TARGET) -w9
LDFLAGS+= $(DEBUG) $(TARGET)

BINS = nomutex mutex prodcons condvar semex

all: $(BINS)

clean:
	rm -f *.o $(BINS) *.tmp

