CC = gcc
CFLAGS = -O2

default: all

server: mathserver/src/server.c
	$(CC) $(CFLAGS) mathserver/src/server.c -lpthread -o server

clientProgram: client/client.c
	$(CC) $(CFLAGS) client/client.c -o clientProgram

all: server clientProgram
clean:
	rm server clientProgram