#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "scaledFootrule.h"
#include "rankList.h"

#define MAX_URL_SIZE 10


int main(int argc, char *argv[]){

	//Error handling
	if(argc < 2){
		printf("Incorrect Input\nUsage: %s [List 1] [List 2] ... [List n]\n", argv[0]);
		return 1;
	}

	FILE *fp;

	int curr_lineCount, i;
	rankList rList = createRankList();

	//Read argument/ranking and place in suitable arrays
	for(i = 1; i < argc; i++){
		if(((fp = fopen(argv[i], "r")) == NULL)){
			printf("%s can not be read\n", argv[i]);
			return 1;
		}
		curr_lineCount = getRankSize(fp);
		insertRankNode(rList, getRankArray(fp, curr_lineCount), curr_lineCount, removeExtension(argv[i]));

	}
	fclose(fp);

	float totalScaledValue = 0;
	char **finalList = malloc(rList->nUnique * sizeof(char*));


	for(i = 0; i < rList->nUnique; i++){
		uniqueNode currUnique = rList->uFirst;
		while(currUnique != NULL){
			rankNode currRank = rList->first; 
			while(currRank != NULL){
				int currRankPos = getRankPos(currUnique->urlName, currRank->nLines, currRank->list);
				if(currRankPos != -1){

					totalScaledValue += fabsf( ((float)currRankPos/ (currRank->nLines) ) - 
										   ( ((float)currUnique->index) / (rList->nUnique) ) );
				}
				currRank = currRank->next;
			}
			currUnique = currUnique->next;
		}	
	}
	finalList = getUniqueList(rList, finalList);
	bruteForce(rList, 0, totalScaledValue, finalList);


	freeRankList(rList);
	return 0;
}

//Get number of lines in file
int getRankSize(FILE *fp){

	char fscanf_buffer[MAX_URL_SIZE];
	int line_count = 0;

	//Count number lines for array declartion
	while(fscanf(fp, "%s", fscanf_buffer) != EOF){
		line_count++;
	}

	return line_count;
}

//Create character array from each line
char** getRankArray(FILE *fp, int size){

	char fscanf_buffer[MAX_URL_SIZE];
	int i = 0;					

	char **returnArray = calloc(size , sizeof(char*));

	rewind(fp);
	while(fscanf(fp, "%s", fscanf_buffer) != EOF){
		returnArray[i] = malloc(strlen(fscanf_buffer) + 1);
		strcpy(returnArray[i], fscanf_buffer);
		i++;
	}

	return returnArray;
}

char* removeExtension(char *url){
	int len = strlen(url) - 4;
	char *noExt = malloc(len + 1);

	memmove(noExt, url, len);
	noExt[len+1] = '\0';
	//printf("DEBUG: url %s noExt %s\n", url, noExt);

	return noExt;
}