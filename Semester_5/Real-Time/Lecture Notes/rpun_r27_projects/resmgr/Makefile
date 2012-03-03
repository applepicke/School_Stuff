
#
#	Makefile for resmgr project (rmintro)
#

BINS = example

DEBUG = -g
CC = qcc
LD = qcc

TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoppcbe

CFLAGS += $(DEBUG) $(TARGET) -w9
LDFLAGS+= $(DEBUG) $(TARGET)

all:	$(BINS)

clean:
	rm -f *.o $(BINS) *.tmp
