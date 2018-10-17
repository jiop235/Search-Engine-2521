#include <stdio.h>

// General structure attributed to week3 lab 2521 DLList.h
// Written by John Shepherd, March 2013
// Last modified, August 2014


typedef struct ListRep *List;

// create a new empty List
List newList();

// free up all space associated with list
void freeList(List);

// add item to list
void insertList(List, char*);

// is the item in the list
int isInList(List, char*);

// check sanity of a List (for testing)
int validList(List);

// return item at current position
char *ListCurrent(List);

// return number of elements in a list
int ListLength(List);

// is the list empty?
int ListIsEmpty(List);

//Print curr and nitems
void showState(List L);

//Print the list
void showList(List L);


/*
// create an List by reading items from a file
// assume that the file is open for reading
List getList(FILE *);

// display list to file, one item per line
// assumes that the file is open for writing
void putList(FILE *, List);
*/
/*
// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
int ListMove(List, int);

// move to specified position in list
// i'th node, assuming first node has i==1
int ListMoveTo(List, int);
*/
