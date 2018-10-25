#define _SVID_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rankList.h"

rankList createRankList(){
	rankList newrankList = malloc(sizeof(struct _rankList));
	if(newrankList == NULL) perror("malloc() failed to allocate rankList\n");
	newrankList->nLists = 0;
	newrankList->first = NULL;

	newrankList->nUnique = 0;
	newrankList->uFirst = NULL;
	newrankList->uLast = NULL; 

	return newrankList;
}

static rankNode createRankNode(int size, char *urlName){
	rankNode new = malloc(sizeof(struct _rankNode));
	if(new == NULL) perror("malloc() failed to allocate rankNode\n");

	new->nLines = size;
	new->list = malloc(size * sizeof(char*));
	if(new->list == NULL) perror("malloc() failed to allocate rankNode->list\n");
	
	new->urlName = urlName;

	new->next = NULL;
	return new;
}

static uniqueNode createUniqueNode(char *urlName, int index){
	uniqueNode new = malloc(sizeof (struct _uniqueNode));
	if(new == NULL) perror("malloc() failed to allocate rankNode\n");

	new->index = index;
	new->urlName = strdup(urlName);
	if(new->urlName == NULL) perror("malloc() failed to allocate rankNode->list\n");

	new->next = NULL;

	return new;
}

void insertRankNode(rankList L, char **List, int size, char *urlName){
	if(L == NULL) return;
	rankNode new = createRankNode(size, urlName);


	//Unique list
	int i;
	for(i = 0; i < size; i++){
		if(UniquePos(List[i], L->uFirst) == -1){
			insertUniqueNode(L, L->nUnique, List[i]);
			L->nUnique++;
		}
	}

	//Insert List values
	new->list = List;

	//Insert rankNode into rankList
	L->nLists++;
	if(L->first == NULL){ 
		L->first = new;
	}else{
		rankNode temp = L->first;
		while(temp->next != NULL) temp = temp->next;
		temp->next = new;
	}

}

void insertUniqueNode(rankList L, int index, char *urlName){
	if(L == NULL) return;
	uniqueNode new = createUniqueNode(urlName, L->nUnique);

	if(L->uFirst == NULL){
		L->uFirst = new;
	}else{
		L->uLast->next = new;
	}
	L->uLast = new;

}

int UniquePos(char *searchURL, uniqueNode first){
	uniqueNode curr = first;
	int pos = 0;
	while(curr != NULL){
		if(strcmp(curr->urlName, searchURL) == 0) return pos;
		pos++;
		curr = curr->next;
	}
	return -1;
}

int getRankPos(char *searchURL, int size, char **array){
	int i;
	for(i = 0; i < size; i++){
		if(strcmp(array[i], searchURL) == 0) return i;
	}
	return -1;
}

void freeRankList(rankList L){

	if(L == NULL) return;
	int i;

	rankNode curr, prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;

		for(i = 0; i < prev->nLines; i++){
			free(prev->list[i]);
		}
		free(prev->list);
		free(prev->urlName);
		free(prev);
	}

	uniqueNode uCurr, uPrev;
	uCurr = L->uFirst;
	while(uCurr != NULL){
		uPrev = uCurr;
		uCurr = uCurr->next;

		free(uPrev->urlName);
		free(uPrev);
	}

}


void showRankList(rankList L){
	if(L == NULL) return;
	int i;
	rankNode curr = L->first;
	while(curr != NULL){
		printf("url: %s nLines: %d\n", curr->urlName, curr->nLines);
		for(i = 0; i < curr->nLines; i++)
			printf("  \u2514--->%s\n", curr->list[i]);
		curr = curr->next;
	}

	uniqueNode uCurr = L->uFirst;
	printf("nUnique: %d\n", L->nUnique);
	while(uCurr != NULL){
		printf("%d) \u2514--->%s\n", uCurr->index, uCurr->urlName);
		uCurr = uCurr->next;
	}
}


int getNumberLists(rankList L){
	return L->nLists;
}


char** getUniqueList(rankList L, char **list){
	

	uniqueNode curr = L->uFirst;
	int i = 0;
	while(curr != NULL){
		list[i] = strdup(curr->urlName);
		curr = curr->next; i++;
	}
	return list;
}


//Brute force method changes unique list order and calculates total scaled value from that
//The intial values are calculated scaledFootrule.c and the rest is recursively calculated
float bruteForce(rankList L, int level, float low, char **finalList){
	int i;
	int nextLevel = level + 1;\
	float lowestScaled = low;
	float totalScaledValue = 0;
	for(i = 0; i < L->nUnique - level; i++){

		lowestScaled = bruteForce(L ,nextLevel ,lowestScaled, finalList);
		swap(L, level);

			uniqueNode currUnique = L->uFirst;
			while(currUnique != NULL){
			//Open every list and check scaled footrule
				rankNode currRank = L->first; 
				while(currRank != NULL){
					int currRankPos = getRankPos(currUnique->urlName, currRank->nLines, currRank->list);
					if(currRankPos != -1){

						totalScaledValue += fabsf( ((float)currRankPos/ (currRank->nLines) ) - 
											   ( ((float)currUnique->index) / (L->nUnique) ) );
					}
					currRank = currRank->next;
				}
				currUnique = currUnique->next;
			}	

		//Change final totalscaled value and get the list
		if(totalScaledValue < lowestScaled){
			lowestScaled = totalScaledValue;
			finalList = getUniqueList(L, finalList);
		}

		//If final interation print values
		if(i == L->nUnique-1 && level == 0){
			printf("Total Scaled Value %f\n", lowestScaled);
			for(i = 0; i < L->nUnique; i++) printf("%s\n", finalList[i]);
		}

	}
	return lowestScaled;
}

void swap(rankList L, int a){
	int index = a;
	uniqueNode curr = L->uFirst;
	while(curr != NULL){
		if(index == curr->index) break;
		curr = curr->next;
	}
	char *temp = L->uLast->urlName;
	L->uLast->urlName = curr->urlName;
	curr->urlName = temp;
}
