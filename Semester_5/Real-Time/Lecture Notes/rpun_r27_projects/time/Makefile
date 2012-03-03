
#
#	Makefile for time project
#

DEBUG = -g
CC = qcc
LD = qcc

TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoppcbe

CFLAGS += $(DEBUG) $(TARGET) -w9
LDFLAGS+= $(DEBUG) $(TARGET)

BINS = calctime1 calctime2 alarm1 timeout1 timeout2 timeout3 \
		reptimer nonblockpulserec

all: $(BINS)

clean:
	rm -f *.o $(BINS) *.tmp

