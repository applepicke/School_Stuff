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
BINS = shmem_cr shmem_usr

#Make target build all
all: $(BINS)

shmem_cr.o: shmem_cr.c prod.h
shmem_usr.o: shmem_usr.c prod.h