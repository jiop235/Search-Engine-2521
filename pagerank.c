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

int main(){


	Graph pageGraph = readCollection("collection.txt");
	totalPageRank(pageGraph, 0.85, 0.00001, 10000);
	showGraph(pageGraph);
	
	int i = 0, j;
	FILE *fp;
	fp = fopen("pagerankList.txt", "w");

	int visited[pageGraph->nV];
	for(i = 0; i < pageGraph->nV; i++) visited[i] = 0;
	float highestPageRank = 0;
	int index;
	for(j = 0; j < pageGraph->nV; j++){
		for(i = 0; i < pageGraph->nV; i++){
			if(visited[i] == 1) continue;
			if(getPageRank(pageGraph->edges[i]) > highestPageRank){
				highestPageRank = getPageRank(pageGraph->edges[i]);
				index = i;
			} 
		}
		fprintf(fp, "%s, %d, %.7f\n", pageGraph->index_URL[index], 
		getOutLinks(pageGraph->edges[index]), getPageRank(pageGraph->edges[index]) );
		visited[index] = 1;
		highestPageRank = 0;
	}

	fclose(fp);
	destroyGraph(pageGraph);
	
	return 0;
	/*
	FILE *fp;
	Graph pageGraph;
	fp = fopen("collection.txt", "r");

	//Read Urls
	char curr_URL[URL_SIZE]; // Dynamically allocate this shit
	int url_count = 0; // Counts the nV / URLS that are in the collection.txt

	//List webSites;

	//Determine size of graph
	while(fscanf(fp, "%s", curr_URL) != EOF){	//Find some way to read each WORD
		printf("%d) testing %s\n", url_count, curr_URL);
		url_count++;
	}
	char *index_URL[url_count - 1];	//Dynamically allocate this shit, HOLDS THE INDEX value to the URL string so (e.g. 0 = url23, 1 = url56 etc)
	pageGraph = createGraph(url_count);
	rewind(fp); 							//Rewinds the fp to start of pointer
	url_count = 0;
	while(fscanf(fp, "%s", curr_URL) != EOF){
		index_URL[url_count] = strdup(curr_URL);
		url_count++;
	}*/



	//Add values into it

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


	//float inP;
	int interation = 0;
	float diff = diffPR;
	//float prevPageRank;
	float sumCurrDiff = 0;

	for(i = 0; i < g->nV; i++){
		getWeightedValues(g->edges[i], g);
	}

	while(interation < maxIterations && diff >= diffPR){
		//printf("interation %d\n", interation);
		for(i = 0; i < g->nV; i++){
			//prevPageRank = getPageRank(g->edges[i]);
			//printf("prevPageRank %f\n", prevPageRank);
			
			printf("CURRENT URL %s\n", g->index_URL[i]);
			newPageRank[i] = ((1 - d)/N) + (d * pageRankCalc(g->edges[i], g));
			//rintf("newPageRank %f\n", newPageRank[i]);
			//changePageRank(g->edges[i], ((1 - d)/N) + (d * pageRankCalc(g->edges[i], g)));

			//printf("after equation %f\n", getPageRank(g->edges[i]));
		}
		for(i = 0; i < g->nV; i++){
			//printf("sumCurrDiff %f %f \n", sumCurrDiff, fabsf(getPageRank(g->edges[i]) - prevPageRank));
			sumCurrDiff += fabsf((newPageRank[i] - getPageRank(g->edges[i])));
			//printf("sumCurrDiff %f\n", sumCurrDiff);
			changePageRank(g->edges[i], newPageRank[i]);
		}
		diff = sumCurrDiff;
		//printf("diff %f\n", diff);
		sumCurrDiff = 0;
		interation++;
	}
	
}

