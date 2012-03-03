# build option variables
DEBUG = -g

# specification of compiler and linker  
CC = qcc
LD = qcc

# specifications for target platform and compiler version
TARGET = -Vgcc_ntox86

# compile and link options
CFLAGS += $(TARGET) $(DEBUG) -w9
LDFLAGS+= $(TARGET) $(DEBUG)

#Binaries to be built
BINS = arithd arithcl

#Make target build all
all: $(BINS)

arithd.o: arithd.c arith.h
arithcl.o: arithcl.c arith.h