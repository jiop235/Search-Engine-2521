#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

//Inpiration from week8 lab 2521 written by John Shepard 2015

typedef struct GraphRep{
	int nV;			//# vertuces
	int nE;
	//int maxV;		//Max vertexs
	//int **edges;	//matrix of weights (0 == no edges)
	List
} GraphRep;

Graph createGraph(int nV){

	//Create GraphRep basic Structure
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	new->nV = nV; new->nE = 0; 
	new->edges = malloc(nV * (sizeof(int *)));
	assert(new->edges != NULL);

	for(v = 0; v < nV; v++){
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != NULL);
		for(w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	
	return new;
}

void destroyGraph(Graph g){
	if(g == NULL) return;
	int i;
	for(i = 0; i < g->nV; i++){
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

void insertEdge(Graph g, Vertex v, Vertex w){
	assert(g != NULL);
	g->edges[v][w] = 1;
	//g->edges[w][v] = 1;
}

int isConnected(Graph g, Vertex v, Vertex w){
	if (v < 0 || w < 0 || v > g->nV || w > g->nV){
		return 0;
	}else{
		return g->edges[v][w];
	}
}

void showGraph(Graph g){
	assert(g != NULL);
	printf("Graph has %d vertices:\n",g->nV);
		int i, j;

		for (i = 0; i < g->nV; i++) {
			for (j = 0; j < g->nV; j++)
				printf("%d",g->edges[i][j]);
			putchar('\n');
		}

		
}
/*
void removeEdge(Graph g, Vertex v, Vertex w){
	assert(g != NULL);
	g->edges[v][w] = 0;
}*/
