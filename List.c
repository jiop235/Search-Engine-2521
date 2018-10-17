// List.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// data structures representing List

typedef struct ListNode {
	char   *string;  // string of this list item (string)
					 //The first value will always be the current URL
					 //Every value after is it outward links!!!!
	struct ListNode *next;
	               // pointer to next node in list
} ListNode;

typedef struct ListRep {
	int  nitems;      // count of items in list
	ListNode *first; // first node in list
	struct ListRep *next;
//	ListNode *last;  // last node in list
} ListRep;

// create a new ListNode (private function)
static ListNode *newListNode(char *it)
{
	ListNode *new;
	new = malloc(sizeof(ListNode));
	assert(new != NULL);
	new->string = strdup(it);
	new->next = NULL;
	return new;
}

// create a new empty List
List newList()
{
	struct ListRep *L;

	L = malloc(sizeof (struct ListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	return L;
}

// free up all space associated with list
void freeList(List L)
{
	assert(L != NULL);
	ListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->string);
		free(prev);
	}
	free(L);
}

void insertList(List L, char *it){
	printf("List %s\n", it);
	L->nitems++;
	printf("List nitems %d\n", L->nitems);
	ListNode *new = newListNode(it);
	if(L->first == NULL){
		L->first = new;
	}else{
		ListNode *curr = L->first;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = new;
	}
}

//Returns 1 if found
int isInList(List L, char* index){
	ListNode *curr = L->first;
	while(curr != NULL){
		if (strcmp(curr->string, index) == 0) return 1;
		curr = curr->next;
	}
	return 0;
}
// check sanity of a List (for testing)
int validList(List L)
{
	if (L == NULL) {
		fprintf(stderr,"List is null\n");
		return 0;
	}
	int count;
	ListNode *curr;
	// check scanning forward through list
	count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next) count++;
	if (count != L->nitems) {
		fprintf(stderr, "Forward count mismatch; counted=%d, nitems=%d\n",
		        count, L->nitems);
		return 0;
	}
	// check scanning backward through list
	count = 0;
	// nothing went wrong => must be ok
	return 1;
}


// return number of elements in a list
int ListLength(List L)
{
	return (L->nitems);
}

// is the list empty?
int ListIsEmpty(List L)
{
	return (L->nitems == 0);
}
void showList(List L){
	printf("\nL->nitems %d\n", L->nitems);
	if(L->nitems != 0){
		ListNode *curr = L->first;
		while(curr != NULL){
			printf("%s", curr->string);
			curr = curr->next;
		}
		//printf("\n");
	}else{
		printf("NULL\n");
	}
}
// return item at current position
/*char *ListCurrent(List L)
{
	assert(L != NULL); assert(L->curr != NULL);
	return L->curr->string;
}

void showState(List L){
	if(L->nitems != 0){
		 printf("| curr -  %s | ", L->curr->string);
	}else{
		printf("| curr - NULL | ");
	}
	printf(" nitems - %d |\n",  L->nitems);
}
// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
// if current is currently null, return 1
int ListMove(List L, int n)
{
	assert(L != NULL);
	if (L->curr == NULL)
		return 1;
	else if (n > 0) {
		while (n > 0 && L->curr->next != NULL) {
			L->curr = L->curr->next;
			n--;
		}
	}
	else if (n < 0) {
		while (n < 0 && L->curr->prev != NULL) {
			L->curr = L->curr->prev;
			n++;
		}
	}
	return (L->curr == L->first || L->curr == L->last) ? 1 : 0;
}

// move to specified position in list
// i'th node, assuming first node has i==1
int ListMoveTo(List L, int i)
{
	assert(L != NULL); assert(i > 0);
	L->curr = L->first;
	return ListMove(L, i-1);
}*/

// trim off \n from strings (private function)
// this is needed for getList() because of fgets()
// alternatively, we could use the evil gets() function
/*static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n') s[end] = '\0';
	return s;
}*/

/*
// create an List by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
List getList(FILE *in)
{
	List L;
	ListNode *new;
	char line[1000];

	L = newList();
	while (fgets(line,1000,in) != NULL) {
		char *string = strdup(trim(line));
		new = newListNode(string);
		if (L->last == NULL) {
			L->first = L->last = new;
		}
		else {
			L->last->next = new;
			new->prev = L->last;
			L->last = new;
		}
		L->nitems++;
	}	
	L->curr = L->first;
	return L;
}

// display list to file, one item per line
// assumes that the file is open for writing
void putList(FILE *out, List L)
{
	assert(out != NULL); assert(L != NULL);
	ListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
		fprintf(out,"%s\n",curr->string);
}*/
