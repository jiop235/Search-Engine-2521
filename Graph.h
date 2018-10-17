//Graph.h ADT
//General structure attributed to week9 2521 lab "Graph.h" written by John Shepard, March 2013

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "List.h"



//Graph Struct
typedef struct GraphRep *Graph;

typedef struct GraphRep{
	int nV;			//# vertuces
	int nE;
	//int maxV;		//Max vertexs
	//int **edges;	//matrix of weights (0 == no edges)
	List *edges;
	char **index_URL;	//Array of urls to there index
} GraphRep;

Graph createGraph(int nV);
void destroyGraph(Graph);

//Vertex
typedef int Vertex;

//Edges = link between 2 vertices
//typedef struct { Vertex v; Vertex w;} Edge; 
void insertEdge(Graph, Vertex, Vertex);//, int);
//

int isConnected(Graph, Vertex, Vertex);
void showGraph(Graph);

#endif
