
#
#	Makefile for hello project
#

DEBUG = -g
CC = qcc
LD = qcc
TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoppcbe


CFLAGS += $(DEBUG) $(TARGET) -w9
LDFLAGS+= $(DEBUG) $(TARGET)

all:	hello

clean:
	rm -f *.o *.img hello *.tmp

