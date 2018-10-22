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
	int index;
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
	new->Wout = -1;
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

void insertIndex(List L, int index){
	L->index = index;
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
			inWeight(g->edges[currIndex], g->index_URL[L->index], temp->Wout, 0);
			inWeight(g->edges[currIndex], g->index_URL[L->index], temp->Win, 1);

		temp = temp->next;

	}
}
void inWeight(List L, char *string, float val, int type){
	ListNode *temp;
	temp = L->inFirst;
	while(temp != NULL){
		printf("tempSring %s string %s\n", temp->string, string);
		if(strcmp(temp->string, string) == 0){
			if(type == 0){
				temp->Wout = val;
			}else{
				temp->Win = val;
			}
			break;
		}
		temp = temp->next;
	}
}
float pageRankCalc(List L, Graph g){
	float result = 0;
	int currIndex;
	float tempNum;

	ListNode *temp;
	
	temp = L->inFirst;
	while(temp != NULL){
		//printf("	URL: %s Win: %.7f Wout: %.7f\n", temp->string, temp->Win, temp->Wout);
		currIndex = URL_to_index(g->index_URL, temp->string);
		tempNum = g->edges[currIndex]->pageRank;

		tempNum *= temp->Win;
	    tempNum *= temp->Wout;
		result += tempNum;

		temp = temp->next;

	}

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
			printf("  \u2514--->%s Win: %.7f Wout %.7f\n",  curr->string, curr->Win, curr->Wout);
			curr = curr->next;
		}
	}else{
		printf("Empty List (NULL)\n");
	}
}
