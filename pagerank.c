#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
//#include "Graph.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

//This is just pseduocode does not currently run - Nathan 15/10 12:34

int main(){

	FILE *fp;
	//Graph pageGraph;
	fp = fopen("collection.txt", "r");

	//Read Urls
	char curr_URL[URL_SIZE]; // Dynamically allocate this shit
	char index_URL[URL_NUM][URL_SIZE];	//Dynamically allocate this shit, HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)
	int url_count = 0; // Counts the nV / URLS that are in the collection.txt


	//Determine size of graph
	while(fscanf(fp, "%s", curr_URL) != EOF){	//Find some way to read each WORD
		strcpy(index_URL[url_count], curr_URL);
		url_count++;
		printf("%d) testing %s\n", url_count, index_URL[url_count]);
	}

	pageGraph = createGraph(url_count);
	//GRAPH should have a data type that holds the index value!
	//Move file pointer to start of string
	fseek(fptr, 0, SEEK_SET);
	while(fscanf(fp, "%s", curr_URL) != EOF){

	}

	//Add values into it

}
