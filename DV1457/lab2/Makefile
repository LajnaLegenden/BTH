CC = gcc
CFLAGS = -O2 -w

default: all

mathserver/server: mathserver/src/server.c
	$(CC) $(CFLAGS) mathserver/src/server.c -lpthread -o mathserver/server

client/client: client/client.c
	$(CC) $(CFLAGS) client/client.c -o client/client

mathserver/matinv-par: mathserver/src/matinv-par.c
	$(CC) $(CFLAGS) mathserver/src/matinv-par.c -lpthread -o mathserver/matinv-par

mathserver/matinv: mathserver/src/matinv.c
	$(CC) $(CFLAGS) mathserver/src/matinv.c -lpthread -o mathserver/matinv

mathserver/kmeans: mathserver/src/kmeans.c
	$(CC) $(CFLAGS) mathserver/src/kmeans.c -lpthread -o mathserver/kmeans

all: mathserver/server client/client mathserver/matinv-par mathserver/kmeans mathserver/matinv
clean:
	rm mathserver/server client/client mathserver/matinv-par mathserver/kmeans mathserver/matinv