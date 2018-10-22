#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define URL_SIZE 10

int findURLindex(char name[][URL_SIZE], char *url, int url_count);

int main(int argc, char *argv[]){
	
	if(argc <= 1){
		printf("Incorrect input\n");
		printf("Usage: %s #word# #word# etc\n", argv[0]);
		return 1;
	}

	FILE *fp;
	char currURL[50];
	int url_count = 0;
	
	if((fp = fopen("pagerankList.txt", "r")) == NULL) return 1;
	
	//Count the number of urls in pagerank to set array sizes
	while(fgets(currURL, 50, fp) != NULL) url_count++;
	rewind(fp);

	char url_name[url_count][URL_SIZE];		//Holds url names for comparison
	char random_buffer[URL_SIZE];
	float url_pageranks[url_count];			
	int url_values[url_count];				//Amount of words found in url

	int i = 0;
	//while(fscanf(fp,"%s%*[^\n]", url_name[i]) != EOF){
	while(fscanf(fp, "%s %s %f", url_name[i], random_buffer, &url_pageranks[i]) == 3){
		url_values[i] = 0;
		url_name[i][strlen(url_name[i]) - 1] = '\0';	//Remove the , 
		i++;
	}

	char *currWord;							//Current word being scanned inverted index
	char *searchWord;						//Word being searched for
	char url_buffer[URL_SIZE];				//Scan urls in invertedIndex when the searchword is found
	char ch;								//Search for \n (will be just a space if not) indicates that the line is over (no more urls)
	int  curr_index;						

	if((fp = fopen("invertedIndex.txt", "r")) == NULL) return 1;

	//Loop through all words and increment url_values
	for(i = 1; i < argc ; i++){
		searchWord = strdup(argv[i]);
		currWord = malloc(strlen(argv[i]) + 1);
		//Read first word on each line an compare with searchWord
		while(fscanf(fp, "%s", currWord) != EOF){
			if(strcmp(currWord, searchWord) == 0){
				//Search through urls until the end of the line
				while(fscanf(fp, "%s%c", url_buffer, &ch) == 2){
					if( (curr_index = findURLindex(url_name, url_buffer, url_count)) != -1){
						url_values[curr_index]++;
					}
					if(ch == '\n') break;
				}
				break;
			}
			fscanf(fp,"%*[^\n]", currWord);		//Read to \n
		}
		rewind(fp);
		free(currWord);

	}

	int url_max = 0;
	for(i = 0; i < url_count; i++){
		if(url_max == 30) break;
		if(url_values[i] > 0){
			printf("%s\n", url_name[i]);
			url_max++;
		} 
	}
	fclose(fp);

	return 0;
}

//
int findURLindex(char name[][URL_SIZE], char *url, int url_count){
	int i;
	for(i = 0; i < url_count; i++){
		if(strcmp(name[i], url) == 0) return i;
	}
	return -1;

}