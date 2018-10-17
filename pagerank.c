#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#include "readData.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

//This is just pseduocode does not currently run - Nathan 15/10 12:34



int main(){


	Graph pageGraph = readCollection("collection.txt");
	showGraph(pageGraph);
	/*
	FILE *fp;
	Graph pageGraph;
	fp = fopen("collection.txt", "r");

	//Read Urls
	char curr_URL[URL_SIZE]; // Dynamically allocate this shit
	int url_count = 0; // Counts the nV / URLS that are in the collection.txt

	//List webSites;

	//Determine size of graph
	while(fscanf(fp, "%s", curr_URL) != EOF){	//Find some way to read each WORD
		printf("%d) testing %s\n", url_count, curr_URL);
		url_count++;
	}
	char *index_URL[url_count - 1];	//Dynamically allocate this shit, HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)
	pageGraph = createGraph(url_count);
	rewind(fp); 							//Rewinds the fp to start of pointer
	url_count = 0;
	while(fscanf(fp, "%s", curr_URL) != EOF){
		index_URL[url_count] = strdup(curr_URL);
		url_count++;
	}*/



	//Add values into it

}

