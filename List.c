// List.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"
#include "readData.h"



// data structures representing List

typedef struct ListNode {
	char   *string;  // string of this list item (string)
					 //The first value will always be the current URL
					 //Every value after is it outward links!!!!
	float Win;
	float Wout;
	struct ListNode *next;
	               // pointer to next node in list
} ListNode;

typedef struct ListRep {
	int outLinks;      // count of items in list
	int inLinks;
	float pageRank;

	ListNode *outFirst; // outFirst node in list
	ListNode *inFirst;
} ListRep;

// create a new ListNode (private function)
static ListNode *newListNode(char *it)
{
	ListNode *new;
	new = malloc(sizeof(ListNode));
	assert(new != NULL);
	new->string = strdup(it);
	new->Win = -1;
	new->Win = -1;
	new->next = NULL;
	return new;
}

// create a new empty List
List newList()
{
	struct ListRep *L;
	L = malloc(sizeof (struct ListRep));
	assert (L != NULL);
	L->outLinks = 0;
	L->pageRank = 0;
	L->inLinks = 0;


	L->outFirst = NULL;
	L->inFirst = NULL;
	return L;
}

// free up all space associated with list
void freeList(List L)
{
	assert(L != NULL);
	ListNode *curr, *prev;
	curr = L->outFirst;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->string);
		free(prev);
	}
	curr = L->inFirst;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->string);
		free(prev);
	}

	free(L);
}

void insertList(List L, char *it, int direction){
	ListNode *new = newListNode(it);
	if(direction == 0){			//InLinks
		L->inLinks++;
		if(L->inFirst == NULL)	{
			L->inFirst = new;
		}else{
			ListNode *curr = L->inFirst;
			while(curr->next != NULL){
				curr = curr->next;
			}
			curr->next = new;
		}	
	}else{						//OutLinks
		L->outLinks++;
		if(L->outFirst == NULL)	{
			L->outFirst = new;
		}else{
			ListNode *curr = L->outFirst;
			while(curr->next != NULL){
				curr = curr->next;
			}
			curr->next = new;
		}	
	}
}

void changePageRank(List L, float num){
	L->pageRank = num;
}

int getOutLinks(List L){
	return L->outLinks;
}

float getPageRank(List L){
	return L->pageRank;
}

void getWeightedValues(List L, Graph g){
	int currIndex;
	float totalOutlinks = 0;
	float totalInlinks = 0;

	ListNode *temp;
	temp = L->outFirst;
	while(temp != NULL){
		currIndex = URL_to_index(g->index_URL, temp->string);
		//printf("curr %d\n", g->edges[currIndex]->outLinks); 
		totalInlinks += (float)g->edges[currIndex]->inLinks;
		if(g->edges[currIndex]->outLinks == 0){ 
			totalOutlinks += 0.5;
		}else{
			totalOutlinks += (float)g->edges[currIndex]->outLinks;
		}
		temp = temp->next;
	}

	temp = L->outFirst;
	while(temp != NULL){
		currIndex = URL_to_index(g->index_URL, temp->string);

		//printf("currIndex %d totalInlinks %f totalOutlink %f \n",
		//	    currIndex, totalInlinks, totalOutlinks);
			temp->Win = (((float)g->edges[currIndex]->inLinks )/ totalInlinks);

			if(g->edges[currIndex]->outLinks == 0){
				temp->Wout = (0.5/ totalOutlinks);
			}else{
				temp->Wout = ((float)g->edges[currIndex]->outLinks/ totalOutlinks);
			}

		temp = temp->next;

	}
}

float pageRankCalc(List L, Graph g){
	float result = 0;
	int currIndex;
	float tempNum;
	//float totalOutlinks = 0;
	//float totalInlinks = 0;

	ListNode *temp;
	//Get PR(A) = PR(B) + PR(C) + PR(D)
	//			   L(B) +  L(C) +  L(D)


	//if(L->outLinks == 0) totalOutlinks += 0.5;
	
	temp = L->outFirst;
	while(temp != NULL){
		printf("	URL: %s Win: %.7f Wout: %.7f\n", temp->string, temp->Win, temp->Wout);
		currIndex = URL_to_index(g->index_URL, temp->string);
		tempNum = g->edges[currIndex]->pageRank;
		tempNum *= temp->Win;
	    tempNum *= temp->Wout;
		result += tempNum;
		//printf("currIndex %d\n", currIndex);
		//if(g->edges[currIndex]->outLinks != 0 ){
			//printf("outLinks %d\n", g->edges[currIndex]->outLinks);
			//PR(B)/L(B)
			//printf("float %f, outLinks %d\n", g->edges[currIndex]->pageRank, g->edges[currIndex]->outLinks);
			//numLink = ((g->edges[currIndex]->pageRank )/ g->edges[currIndex]->outLinks);
			//numLink = g->edges[currIndex]->pageRank;
			//printf("1) numLink %f\n", numLink);
			//printf("3) numLink %f\n", numLink);
			//result += numLink;
			//printf("result %f\n", result);
		//}

		temp = temp->next;

	}

	printf("returned %f\n", result);
	return result;
}

//Returns 1 if found
int isInList(List L, char* index){
	ListNode *curr = L->outFirst;
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
	for (curr = L->outFirst; curr != NULL; curr = curr->next) count++;
	if (count != L->outLinks) {
		fprintf(stderr, "Forward count mismatch; counted=%d, outLinks=%d\n",
		        count, L->outLinks);
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
	return (L->outLinks);
}

// is the list empty?
int ListIsEmpty(List L)
{
	return (L->outLinks == 0);
}
void showList(List L){
	printf(" nLinks: %d outLinks %d\n",  L->inLinks, L->outLinks);
	if(L->outLinks != 0){
		ListNode *curr = L->outFirst;
		printf("OutLinks:\n");
		while(curr != NULL){
			printf("  \u2514--->%s Win: %.7f Wout %.7f\n",  curr->string, curr->Win, curr->Wout);
			curr = curr->next;
		}
	}else{
		printf("Empty List (NULL)\n");
	}

	if(L->inLinks != 0){
		ListNode *curr = L->inFirst;
		printf("Inlinks:\n");
		while(curr != NULL){
			printf("  \u2514--->%s\n",  curr->string);
			curr = curr->next;
		}
	}else{
		printf("Empty List (NULL)\n");
	}
}
// return item at current position
/*char *ListCurrent(List L)
{
	assert(L != NULL); assert(L->curr != NULL);
	return L->curr->string;
}

void showState(List L){
	if(L->outLinks != 0){
		 printf("| curr -  %s | ", L->curr->string);
	}else{
		printf("| curr - NULL | ");
	}
	printf(" outLinks - %d |\n",  L->outLinks);
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
	return (L->curr == L->outFirst || L->curr == L->last) ? 1 : 0;
}

// move to specified position in list
// i'th node, assuming outFirst node has i==1
int ListMoveTo(List L, int i)
{
	assert(L != NULL); assert(i > 0);
	L->curr = L->outFirst;
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
			L->outFirst = L->last = new;
		}
		else {
			L->last->next = new;
			new->prev = L->last;
			L->last = new;
		}
		L->outLinks++;
	}	
	L->curr = L->outFirst;
	return L;
}

// display list to file, one item per line
// assumes that the file is open for writing
void putList(FILE *out, List L)
{
	assert(out != NULL); assert(L != NULL);
	ListNode *curr;
	for (curr = L->outFirst; curr != NULL; curr = curr->next)
		fprintf(out,"%s\n",curr->string);
}*/
