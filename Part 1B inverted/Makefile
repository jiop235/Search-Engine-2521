CC=gcc
CFLAGS=-Wall -Werror
CDEBUG=-Wall -Werror -g
OBJS=inverted.o Graph.o List.o readData.o

all: inverted

inverted: $(OBJS)
	$(CC) -o inverted $(OBJS)

Graph.o: Graph.c Graph.h List.h readData.h
	$(CC) -c $(CLFAGS) Graph.c

List.o: List.c List.h Graph.h readData.h
	$(CC) -c $(CFLAGS) List.c

readData.o: readData.c List.h Graph.h readData.h
	$(CC) -c $(CFLAGS) readData.c

inverted.o: inverted.c inverted.h readData.h Graph.h List.h
	$(CC) -c $(CFLAGS) inverted.c

clean:
	rm -f inverted $(OBJS)
