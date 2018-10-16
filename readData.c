#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

Graph readCollection(char* collection){
	FILE *fp;
	Graph pageGraph;
	fp = fopen(collection, "r");

	//Read Urls
	char curr_URL[URL_SIZE]; // Dynamically allocate this shit
	int url_count = 0; // Counts the nV / URLS that are in the collection.txt

	//List webSites;

	//Determine size of graph
	while(fscanf(fp, "%s", curr_URL) != EOF){	//Find some way to read each WORD
		printf("%d) testing %s\n", url_count, curr_URL);
		url_count++;
	}

	//HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)
	//char *index_URL[url_count - 1];	
	pageGraph = createGraph(url_count);
	rewind(fp); 							//Rewinds the fp to start of pointer
	url_count = 0;
	while(fscanf(fp, "%s", curr_URL) != EOF){
		pageGraph->index_URL[url_count] = strdup(curr_URL);
		url_count++;
	}
	int i = 0;
	for(i = 0; i < url_count; i++) printf("%d) %s\n", i, pageGraph->index_URL[i]);

	fclose(fp);

	return pageGraph;
}


//Translate URL to index
int URL_to_index(char *index_URL[], char *URL){
	int i = 0;
	while(index_URL[i] != NULL){
		if(strcmp(index_URL[i], URL) == 0) return i;
		i++;
	}
	return -1;
}

//Transalte index to URL
char* index_to_URL(char *index_URL[], int index){
	if (index_URL[index] != NULL) return index_URL[index];
	return NULL;
}