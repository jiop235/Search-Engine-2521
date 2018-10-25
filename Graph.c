#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

//Inspiration/Basuc Structure (and some code) from week8 lab 2521 written by John Shepard 2015


Graph createGraph(int nV){

	//Create GraphRep basic Structure
	assert(nV > 0);
	int i;

	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	new->nV = nV; 

	//Malloc Array of Lists
	new->edges = malloc(nV * (sizeof(List)));
	assert(new->edges != NULL);
	for(i = 0;i < nV;i++)
		new->edges[i] = newList();

	new->index_URL = malloc(nV * sizeof(char*));
	
	return new;
}

void destroyGraph(Graph g){
	if(g == NULL) return;
	int i;

	//Free Array of lists
	for(i = 0; i < g->nV; i++)
		freeList(g->edges[i]);
	free(g->edges);

	for(i = 0; i < g->nV; i++)
		free(g->index_URL[i]);
	free(g->index_URL);
	free(g);
}

void insertEdge(Graph g, Vertex v, Vertex w){
	assert(g != NULL);
	if(v == w) return;
	insertList(g->edges[w], g->index_URL[v], 0);	//Track the inLinks
	insertList(g->edges[v], g->index_URL[w], 1);	//Track the outLinks
}

int isConnected(Graph g, Vertex v, Vertex w){
	if (v < 0 || w < 0 || v > g->nV || w > g->nV){
		return 0;
	}else{
		return isInList(g->edges[v], g->index_URL[w]);
	}
}

void showGraph(Graph g){
	assert(g != NULL);

	printf("\n------SHOWING GRAPH------\n\n");
	printf("Graph has %d vertices:\n",g->nV);
	int i;
	for (i = 0; i < g->nV; i++) {
		printf("%d) URL: %s ", i, g->index_URL[i]);
		showList(g->edges[i]);
	}
	printf("\n\n------END GRAPH------\n");	
}

