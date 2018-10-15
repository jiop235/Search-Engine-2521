CC=gcc
CFLAGS=-Wall -Werror
CDEBUG=-Wall -Werror -g
OBJS=pagerank.o Graph.o

all: pagerank

pagerank: $(OBJS)
	$(CC) -o pagerank $(OBJS)

pagerank.o: pagerank.c Graph.h
	$(CC) -c $(CLFAGS) pagerank.c

Graph.o: Graph.c Graph.h
	$(CC) -c $(CLFAGS) Graph.c

clean:
	rm -f pagerank $(OBJS)