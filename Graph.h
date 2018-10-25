//Graph.h ADT
//General structure attributed to week9 2521 lab "Graph.h" written by John Shepard, March 2013

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "List.h"



//Graph Struct
typedef struct GraphRep *Graph;

typedef struct GraphRep{
	int nV;			    // Number of vertices
	//int nE;
	List *edges;
	char **index_URL;	//Array of urls with there respective index 
						//(index is used to determine which url is being processed)
} GraphRep;

//Create a new graph structure to the amount of urls
Graph createGraph(int nV);

//Destroy inputed graph
void destroyGraph(Graph);

//Vertex
typedef int Vertex;

//Insert edge between v and w creates an inlink for w and outlink for v
void insertEdge(Graph g, Vertex v, Vertex w);

//Check if the Vertexes are connnected for debugging purposes
int isConnected(Graph g, Vertex v , Vertex w);

//Show the graph in command line interface for debugging purposes
void showGraph(Graph g);



/* List.c functions that rely on Graph for values 
 * (values outside of give list) as Graph.h has higher priority then List.h
 */
//List.c function calculate Win and Wout values puts it in outLink list (values transferred to inLinks list as required for equation)
void getWeightedValues(List L, Graph g);

//Calculate the summation(PR * Win * Wout)
float pageRankCalc(List L, Graph);


#endif