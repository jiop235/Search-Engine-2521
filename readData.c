#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "Graph.h"
#include "List.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

int collectionLength(char* file){
	FILE *fp;
	if((fp = fopen(file, "r")) == NULL) return -1;

	char buffer[URL_SIZE];
	int url_count = 0;

	while(fscanf(fp, "%s", buffer) != EOF){
		url_count++;
	}

	fclose(fp);
	return url_count;
}

char** getCollection(char* file, int size){
	FILE *fp;
	if((fp = fopen(file, "r")) == NULL) return NULL;

	char buffer[URL_SIZE];
	char **index_URL = calloc(size, sizeof(char*));
	int url_count = 0;

	while(fscanf(fp, "%s", buffer) != EOF){
		index_URL[url_count] = malloc(strlen(buffer) + 1);
		strcpy(index_URL[url_count], buffer);
		url_count++;
	}

	recurInsertion(index_URL, size);
	fclose(fp);
	return index_URL;
}


Graph makeGraph(int url_count, char **index_URL){
	Graph pageGraph;

	pageGraph = createGraph(url_count);

	//g->index_URL[] - HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)

	pageGraph->index_URL = index_URL;

	//Put urls in the graph from 
	insert_URLS(pageGraph);

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

char *normalise(char *string) {
	//Remove . , ; ? if they appear at END OF WORD
	if (string[strlen(string) - 1] == '.'
	|| string[strlen(string) - 1] == ','
	|| string[strlen(string) - 1] == ';'
	|| string[strlen(string) - 1] == '?') {
		string[strlen(string) - 1] = '\0';
	}

	//Converting all characters to lowercase
	int i = 0;
	while (string[i] != '\0') {
		//If the character is upper cases
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = string[i] - 'A' + 'a';
		}

		i++;
	}

	return string;
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

void recurInsertion(char **arr, int size){

	if(size <= 1) return;

	recurInsertion(arr, size - 1);

	int i = size - 2;
	char *tail = arr[size - 1];

	while(i >= 0 && strcmp(arr[i], tail) > 0 ){
		arr[i+1] = arr[i];
		i--;
	}
	arr[i+1] = tail;

}
