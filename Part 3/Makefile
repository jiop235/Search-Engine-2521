CC=gcc
CFLAGS=-Wall -Werror
CDEBUG=-Wall -Werror -g
OBJS=scaledFootrule.o rankList.o

all: scaledFootrule

scaledFootrule: $(OBJS)
	$(CC) -o scaled $(OBJS)

scaledFootrule.o: scaledFootrule.c scaledFootrule.h rankList.h
	$(CC) -c $(CFLAGS) scaledFootrule.c

rankList.o: rankList.c rankList.h
	$(CC) -c $(CFLAGS) rankList.c

clean:
	rm -f scaled $(OBJS)
