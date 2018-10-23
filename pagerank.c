#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "List.h"
#include "readData.h"

#define FALSE 0
#define TRUE 1
#define URL_NUM 10
#define URL_SIZE 30

//This is just pseduocode does not currently run - Nathan 15/10 12:34


void totalPageRank (Graph g, float d, float diffPR, int maxIterations);
void createPageList(Graph g);

int main(){

	Graph pageGraph = readCollection("collection.txt");
	totalPageRank(pageGraph, 0.85, 0.00001, 10000);
	showGraph(pageGraph);
	createPageList(pageGraph);
	destroyGraph(pageGraph);
	return 0;

}

void totalPageRank (Graph g, float d, float diffPR, int maxIterations){
	if(g == NULL) return;
	int N = g->nV, i;
	float one = 1;
	float newPageRank[N];
	//Set initial PageRank
	
	for(i = 0; i < N; i++){
		changePageRank(g->edges[i] , one/N);
		newPageRank[i] = 0;
	}

	int interation = 0;
	float diff = diffPR;
	float sumCurrDiff = 0;

	//Set the weighted values
	for(i = 0; i < g->nV; i++){
		getWeightedValues(g->edges[i], g);
	}

	while(interation < maxIterations && diff >= diffPR){
		//Get the new page ranks for the next interation
		//pageRankCalc calculation summation part of equation.
		for(i = 0; i < g->nV; i++){
			newPageRank[i] = ((1 - d)/N) + (d * pageRankCalc(g->edges[i], g));
		}
		for(i = 0; i < g->nV; i++){
			sumCurrDiff += fabsf((newPageRank[i] - getPageRank(g->edges[i])));
			changePageRank(g->edges[i], newPageRank[i]);
		}
		diff = sumCurrDiff;
		sumCurrDiff = 0;
		interation++;
	}
	
}

void createPageList(Graph g){

	int i, j;
	float highestPageRank = 0;
	int index;		
	int visited[g->nV];
	//Set visited to 0
	for(i = 0; i < g->nV; i++) visited[i] = 0;
	
	FILE *fp;
	fp = fopen("pagerankList.txt", "w");
	if(fp == NULL) return;
	

	//Insertion Sort sorting
	for(j = 0; j < g->nV; j++){
		for(i = 0; i < g->nV; i++){
			if(visited[i] == 1) continue;
			if(getPageRank(g->edges[i]) > highestPageRank){
				highestPageRank = getPageRank(g->edges[i]);
				index = i;
			} 
		}
		fprintf(fp, "%s, %d, %.7f\n", g->index_URL[index], 
		getOutLinks(g->edges[index]), getPageRank(g->edges[index]) );
		visited[index] = 1;
		highestPageRank = 0;
	}

	fclose(fp);
}