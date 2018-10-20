#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#include "readData.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

Graph readCollection(char* collection){
	FILE *fp;
	Graph pageGraph;
	if((fp = fopen(collection, "r")) == NULL) return NULL;

	//Read Urls
	char curr_URL[URL_SIZE]; // Dynamically allocate this shit
	int url_count = 0; 		 // Counts the nV / URLS that are in the collection.txt

	//Determine size of graph and initialise
	while(fscanf(fp, "%s", curr_URL) != EOF){	//Find some way to read each WORD
		printf("%d) testing %s\n", url_count, curr_URL);
		url_count++;
	}
	pageGraph = createGraph(url_count);

	//g->index_URL[] - HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)

	//Load URLS into the g->index_URLS[]
	rewind(fp); 							//Rewinds the fp to start of pointer
	url_count = 0;
	while(fscanf(fp, "%s", curr_URL) != EOF){
		pageGraph->index_URL[url_count] = strdup(curr_URL);
		url_count++;
	}

	insert_URLS(pageGraph);
	fclose(fp);

	return pageGraph;
}


void insert_URLS(Graph g){
	int i;

	for(i = 0; i < g->nV; i++){
		insertIndex(g->edges[i], i);
		FILE *fp;
		//Add .txt at end of string
		char *curr_URL = malloc(sizeof(g->index_URL[i]) + 5);
		strcpy(curr_URL, g->index_URL[i]);
		strcat(curr_URL, ".txt");

		fp = fopen(curr_URL, "r");
		if(fp == NULL){ printf("URL.txt does not exist\n"); break;}
		char curr_string[URL_SIZE];

		while(fscanf(fp, "%s", curr_string) != EOF){
			if(strcmp(curr_string, "#end") == 0){ break; }
			else if((strcmp(curr_string,"#start") == 0) || (strcmp(curr_string,"Section-1") == 0)){
				continue;
			}else{
				insertEdge(g, i, URL_to_index(g->index_URL, curr_string));
			}
		}

		fclose(fp);
		free(curr_URL);
	}
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
