
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

BINS = pps_client_notify pps_client_select pps_publisher

all: $(BINS)

clean:
	rm -f *.o $(BINS) *.tmp

