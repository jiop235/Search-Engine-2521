#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

//Inpiration from week8 lab 2521 written by John Shepard 2015


Graph createGraph(int nV){

	//Create GraphRep basic Structure
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	new->nV = nV; new->nE = 0; 
	new->edges = malloc(nV * (sizeof(List)));
	assert(new->edges != NULL);

	new->index_URL = malloc(nV * sizeof(char*));

	/*for(v = 0; v < nV; v++){
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != NULL);
		for(w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}*/
	
	return new;
}

void destroyGraph(Graph g){
	if(g == NULL) return;
	int i;
	for(i = 0; i < g->nV; i++){
		freeList(g->edges[i]);
		//free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

void insertEdge(Graph g, Vertex v, Vertex w){
	assert(g != NULL);
	insertList(g->edges[v], g->index_URL[w]);
	//g->edges[v][w] = 1;
	//g->edges[w][v] = 1;
}

int isConnected(Graph g, Vertex v, Vertex w){
	if (v < 0 || w < 0 || v > g->nV || w > g->nV){
		return 0;
	}else{
		//return g->edges[v][w];
		return isInList(g->edges[v], g->index_URL[w]);
	}
}

void showGraph(Graph g){
	assert(g != NULL);
	printf("Graph has %d vertices:\n",g->nV);
		int i;

		for (i = 0; i < g->nV; i++) {
			printf("%d) URL: %s\n", i, g->index_URL[i]);
			showList(g->index_URL[i]);
		}

		
}
/*
void removeEdge(Graph g, Vertex v, Vertex w){
	assert(g != NULL);
	g->edges[v][w] = 0;
}*/
