#
#	Makefile for QNX native ipc course module
#

# build option variables
DEBUG = -g

# specification of compiler and linker  
CC = qcc
LD = qcc

# specifications for target platform and compiler version
TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoppcbe


# compile and link options
CFLAGS += $(TARGET) $(DEBUG) -w9
LDFLAGS+= $(TARGET) $(DEBUG)

# binaries to be built
BINS = server client iov_server iov_client disconnect_server disconnect_client \
unblock_server unblock_client event_server event_client \
pps_client_notify pps_client_select pps_publisher shmem_creator shmem_user \
prod_server prod_client

# uncomment for the pulse client and server exercise:
#BINS += pulse_server pulse_client

# uncomment for the name_attach/name_open exerise:
BINS += name_lookup_server name_lookup_client

# uncomment for the multi-part message exercise:
#BINS += iov_client_ex iov_server_ex

# make target to build all
all: $(BINS)

# make target to clean up object files, binaries and stripped (.tmp) files
clean:
	rm -f *.o $(BINS)  *.tmp

# dependencies

server.o: server.c msg_def.h
client.o: client.c msg_def.h

pulse_server.o: pulse_server.c msg_def.h
pulse_client.o: pulse_client.c msg_def.h

name_lookup_server.o: name_lookup_server.c msg_def.h
name_lookup_client.o: name_lookup_client.c msg_def.h

iov_server.o: iov_server.c iov_server.h
iov_client.o: iov_client.c iov_server.h

disconnect_server.o: disconnect_server.c linked_list.h
disconnect_client.o: disconnect_client.c linked_list.h

unblock_server.o: unblock_server.c linked_list.h
unblock_client.o: unblock_client.c linked_list.h

event_server.o: event_server.c event_server.h
event_client.o: event_client.c event_server.h

pps_client_notify.o: pps_client_notify.c pps_def.h
pps_client_select.o: pps_client_select.c pps_def.h
pps_publisher.o: pps_publisher.c pps_def.h

# server to compute product of two numbers
prod_server.o: prod_server.c prod.h
prod_client.o: prod_client.c prod.h