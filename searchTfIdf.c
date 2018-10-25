#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "readData.h"
#include "tfidf.h"

int main (int argc, char *argv[]) {
	if(argc <= 1){
		printf("Incorrect input\n");
		printf("Usage: %s #word# #word# etc\n", argv[0]);
		return 1;
	}

	int pageLength = collectionLength("collection.txt");
	char **index_URL = getCollection("collection.txt", pageLength);
	int i;
	float tfidf_Val[pageLength];

	//Get tfidf_page values for each page
	for(i = 0; i < pageLength; i++){
		char *urlName = malloc(strlen(index_URL[i]) + 5);
		strcpy(urlName, index_URL[i]);
		strcat(urlName, ".txt");
		tfidf_Val[i] = tfidf_page(pageLength, urlName, argc, argv);
		free(urlName);
	}


	int visited[pageLength];
	for(i = 0; i < pageLength; i++) visited[i] = 0;

	//Basic insertion sort inserting highest value
	float highest_tfidf = 0;
	int index, j;
	for(j = 0; j < pageLength; j++){
		for(i = 0; i < pageLength; i++){
			if(visited[i] == 1) continue;
			if(tfidf_Val[i] > highest_tfidf){
				highest_tfidf = tfidf_Val[i];
				index = i;
			}
		}
		if(highest_tfidf != 0){ 
			printf("%s %f\n", index_URL[index], tfidf_Val[index]);
			visited[index] = 1;
		}	
		highest_tfidf = 0;
	}

	for (i = 0; i < pageLength; i++)
		free(index_URL[i]);
	free(index_URL);
	return 1;
}