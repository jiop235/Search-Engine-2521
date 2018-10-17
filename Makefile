CC=gcc
CFLAGS=-Wall -Werror
CDEBUG=-Wall -Werror -g
OBJS=pagerank.o Graph.o List.o readData.o

all: pagerank

pagerank: $(OBJS)
	$(CC) -o pagerank $(OBJS)

pagerank.o: pagerank.c Graph.h
	$(CC) -c $(CFLAGS) pagerank.c

Graph.o: Graph.c Graph.h List.h readData.h
	$(CC) -c $(CLFAGS) Graph.c

List.o: List.c List.h
	$(CC) -c $(CFLAGS) List.c

readData.o: readData.c List.h Graph.h readData.h
	$(CC) -c $(CFLAGS) readData.c

clean:
	rm -f pagerank $(OBJS)
