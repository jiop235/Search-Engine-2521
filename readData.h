#include <stdio.h>
#include "Graph.h"
#include "List.h"

Graph readCollection(char*);

//insert URL into graph

int collectionLength(char* file);
char** getCollection(char* file, int size);
Graph makeGraph(int url_count, char **index_URL);
void insert_URLS(Graph g);
int URL_to_index(char *index_URL[], char *URL);
char* index_to_URL(char *index_URL[], int index);