#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

typedef struct GraphRep{
	int nV;			//# vertuces
	int maxV;		//Max vertexs
	int **edges;	//matrix of weights (0 == no edges)
} GraphRep;

Graph createGraph(int maxV){
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	int i, j;
}