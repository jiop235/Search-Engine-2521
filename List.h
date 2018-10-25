#include <stdio.h>
#include "Graph.h"

// General structure attributed to week3 lab 2521 DLList.h
// Written by John Shepherd, March 2013
// Last modified, August 2014


typedef struct ListRep *List;

// create a new empty List
List newList();

// free up all space associated with list
void freeList(List);

// add item to list (direction either 0 = inLinks, 1 = outLinks)
void insertList(List, char*, int direction);

// is the item in the list
int isInList(List, char*);

// insert index value (index value of index_URL[])
void insertIndex(List L, int index);

//Change the value in pageRank
void changePageRank(List, float);

//Get the outlinks value from List
int getOutLinks(List);

//Get pageRank from List
float getPageRank(List);

//Transfer Weight value from outLinks to inLinks
void inWeight(List L, char *string, float val, int);


//Calculate pageRank Weights etc...
//int pageRankCalc(List L, Graph);		Defined in Graph.h as it require Graph structure
//.h Hierach Graph.h > List.h > etc.h

//Show the whole list
void showList(List);

