#include <stdio.h>
#include "Graph.h"
#include "List.h"

Graph readCollection(char*);

//insert URL into graph
void insert_URLS(Graph g);
int URL_to_index(char *index_URL[], char *URL);
char* index_to_URL(char *index_URL[], int index);