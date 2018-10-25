#include <stdio.h>
#include "Graph.h"
#include "List.h"

Graph readCollection(char*);

//insert URL into graph

//Return the number of lines within the given collection
int collectionLength(char* file);

//Return the urls within collection in a array
char** getCollection(char* file, int size);

//Makes a graph from an array of urls and lines of urls
Graph makeGraph(int url_count, char **index_URL);

//Insert the URLS into edges on the graph
void insert_URLS(Graph g);

//Function normalises and returns the input string
char *normalise(char *string);

//Translates a given URL name and gives its index value;
int URL_to_index(char *index_URL[], char *URL);
//char* index_to_URL(char *index_URL[], int index);

//Recursively insert sort
void recurInsertion(char **arr, int size);