#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RankList.h"

rankList createRankList(){
	rankList newrankList = malloc(sizeof(struct _rankList));
	if(newrankList == NULL) perror("malloc() failed to allocate rankList\n");
	newrankList->nLists = 0;
	newrankList->first = NULL;

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

void insertRankNode(rankList L, char **List, int size, char *urlName){
	rankNode new = createRankNode(size, urlName);

	//Insert List values
	new->list = List;
	/*for(i = 0; i < size; i++){
		new->list[i] = strdup(List[i]);
		if(new->list[i] == NULL) perror("malloc() failed to allocate rankNode->list[] = %s\n", List[i]);
	}*/

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
}