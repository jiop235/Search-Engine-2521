//Graph.h ADT
//General structure attributed to week9 2521 lab "Graph.h" written by John Shepard, March 2013

#include <stdio.h>

//Graph Struct
typedef struct GraphRep *Graph;
Graph createGraph(int nV);
void destroyGraph(Graph);

//Vertex
typedef int Vertex;

//Edges = link between 2 vertices
typedef struct { Vertex v; Vertex w;} Edge; 
void insertEdge(Graph, Vertex, Vertex, int);
void removeEdge(Graph, Vertex, Vertex);

int isConnected(Graph, Vertex, Vertex);
void showGraph(Graph);
