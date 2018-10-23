#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#include "readData.h"
#include "tfidf.h"

int main (int argc, char *argv[]) {
	if(argc <= 1){
		printf("Incorrect input\n");
		printf("Usage: %s #word# #word# etc\n", argv[0]);
		return 1;
	}
	Graph pageGraph = readCollection("collection.txt");
	int i;
	float tfidf_Val[pageGraph->nV];
	for(i = 0; i < pageGraph->nV; i++){
		char *urlName = malloc(strlen(pageGraph->index_URL[i]) + 5);
		strcpy(urlName, pageGraph->index_URL[i]);
		strcat(urlName, ".txt");
		tfidf_Val[i] = tfidf_page(pageGraph, urlName, argc, argv);
		free(urlName);
		
	}
	int visited[pageGraph->nV];
	for(i = 0; i < pageGraph->nV; i++) visited[i] = 0;

	float highest_tfidf = 0;
	int index, j;
	for(j = 0; j < pageGraph->nV; j++){
		for(i = 0; i < pageGraph->nV; i++){
			if(visited[i] == 1) continue;
			if(tfidf_Val[i] > highest_tfidf){
				highest_tfidf = tfidf_Val[i];
				index = i;
			}
		}
		if(highest_tfidf != 0){ 
			printf("%s %f\n", pageGraph->index_URL[index], tfidf_Val[index]);
			visited[index] = 1;
		}	
		highest_tfidf = 0;
	}


	destroyGraph(pageGraph);

	return 1;
}