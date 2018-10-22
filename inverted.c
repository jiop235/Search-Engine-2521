#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "Graph.h"
#include "List.h"
#include "inverted.h"

#define FALSE 0
#define TRUE 1
#define MAX_LINE_LEN 1024
#define FIRST_LINE 1

//Function creates a new URLList with the input string
URLList *newURLList(void) {
	URLList *new;
	new = malloc(sizeof(struct URLList));
	new->first = NULL;
	new->last = NULL;
	return new;
}

//Function creates a new URLNode with the input string
URLNode *newURLNode(char *string) {
	URLNode *new;
	new = malloc(sizeof(URLNode));
	new->string = strdup(string);
	new->next = NULL;
	return new;
}

//Function creates a node for string and inserts the node at the end of list
void insertURLNode(URLList *words, char *string) {
	URLNode *new = newURLNode(string);
	if (words->first == NULL) {
		words->first = new;
	} else {
		URLNode *curr = words->first;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = new;
	}
}

int main(){
	Graph pageGraph = readCollection("collection.txt");
	invertedIndex(pageGraph);
	sort_index("invertedIndex.txt");
	return 0;
}



void invertedIndex(Graph g) {
	int first_line = TRUE;	//If it is the first line of the invertedIndex.txt file
	//Create the file invertedIndex.txt
	FILE *fp = NULL;
	fp = fopen("invertedIndex.txt", "w");
	fclose(fp);
	//Create a linked list to store words that have been encountered
	URLList *words = newURLList();

	//For every URL in the graph, via index_URL
	int i = 0;
	while (i < g->nV) {
		 //Get the url file name from index_URL
		char *curr_url = malloc(strlen(g->index_URL[i]) + strlen(".txt") + 1);
		curr_url[0] = '\0';
 		strcat(curr_url, g->index_URL[i]);
 		strcat(curr_url, ".txt");
 		//Append '.txt' at the end of curr_url

 		FILE *url_fp = NULL;
 		url_fp = fopen(curr_url, "r");
 		//Open the url file for reading
	 		//Loop through entire file to search for unseen words, in Section-2
	 		char *curr_string = malloc(MAX_LINE_LEN);
	 		curr_string[0] = '\0';

	 		int paragraph_started = FALSE;	//Whether fscanf has scanned into the paragraph of words
	 		//Scan every word in the entire url.txt file
	 		while (fscanf(url_fp, "%s", curr_string) != EOF) {
	 			if (strcmp(curr_string, "Section-2") == 0) {
		 		//Section-2 has started
	 				paragraph_started = TRUE;
	 				continue;
	 			} else if (paragraph_started == TRUE && strcmp(curr_string, "#end") == 0) {
	 			//Section-2 has ended
	 				break;
	 			}

	 			//fscanf is scanning the words in Section-2
	 			if (paragraph_started == TRUE) {
					curr_string = normalise(curr_string);
		 			if (word_encountered(words, curr_string) == FALSE) {
		 				//Add curr_string to the 'words' linked list
		 				insertURLNode(words, curr_string);

						FILE *fp = NULL;
						fp = fopen("invertedIndex.txt", "a");
							//Do not print a new line if it is the first line
							if (first_line == TRUE) {
								fprintf(fp, "%s ", curr_string);
								first_line = FALSE;
							} else {
								fprintf(fp, "\n%s ", curr_string);
							}

						fclose(fp);
		 				find_and_insert(g, curr_string);
		 				//Find occurrences of curr_string in all of the urls, and note the relevant urls in invertedIndex.txt
		 				//Exclude 'curr_url' in the search
		 			}
	 			}
	 		}
	 	free(curr_string);
 		fclose(url_fp);
		free(curr_url);
		i++;
	}

	//Append word into invertedIndex.txt

	//Search for its occurrence across all urls
	//If found in an url, append that url to the inverted index section for that word
}

char *normalise(char *string) {
	//Remove . , ; ? if they appear at END OF WORD
	if (string[strlen(string) - 1] == '.'
	|| string[strlen(string) - 1] == ','
	|| string[strlen(string) - 1] == ';'
	|| string[strlen(string) - 1] == '?') {
		string[strlen(string) - 1] = '\0';
	}

	//Converting all characters to lowercase
	int i = 0;
	while (string[i] != '\0') {
		//If the character is upper cases
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = string[i] - 'A' + 'a';
		}

		i++;
	}

	return string;
}

int word_encountered(URLList *words, char *string) {
	URLNode *curr = words->first;
	while (curr != NULL) {
		if (strcmp(curr->string, string) == 0) {
			return 1;
		}
		curr = curr->next;
	}

	return 0;
}

void find_and_insert(Graph g, char *string) {
	int i = 0;
	while (i < g->nV) {
		//Get the url file name from index_URL
		char *curr_url = malloc(strlen(g->index_URL[i]) + strlen(".txt") + 1);
		curr_url[0] = '\0';
 		strcat(curr_url, g->index_URL[i]);
 		strcat(curr_url, ".txt");
 		//Append '.txt' at the end of curr_url
		/*
 		//Skip, if 'curr_url' is the URL that we want to exclude
 		if (strcmp(curr_url, exclude) == 0) {
 			i++;
 			continue;
 		}
 		*/
 		FILE *url_fp = NULL;
 		url_fp = fopen(curr_url, "r");
 		//Open the url file
	 		//Loop through entire file to search for 'string'
	 		char *curr_string = malloc(MAX_LINE_LEN);
	 		curr_string[0] = '\0';
	 		int found = FALSE;
	 		int paragraph_started = FALSE;
	 		while (fscanf(url_fp, "%s", curr_string) != EOF && found != TRUE) {
	 			if (strcmp(curr_string, "Section-2") == 0) {
		 		//Section-2 has started
	 				paragraph_started = TRUE;
	 				continue;
	 			} else if (paragraph_started == TRUE && strcmp(curr_string, "#end") == 0) {
	 			//Section-2 has ended
	 				break;
	 			} 	

	 			//fscanf is scanning the words in Section-2
	 			if (paragraph_started == TRUE) {
		 			curr_string = normalise(curr_string);
		 			//If the word we want to search for is found in the file
		 			if (strcmp(curr_string, string) == 0) {
		 				FILE *fp = NULL;
						fp = fopen("invertedIndex.txt", "a");
							//Append the current URL to the inverted index for 'string'
							//g->index_URL[i] does not have the .txt appended at the end
							fprintf(fp, " %s", g->index_URL[i]);
						fclose(fp);
						found = TRUE;
						//Stop searching the current URL file
		 			}
	 			}
	 		}
	 	free(curr_string);
 		fclose(url_fp);
		free(curr_url);
		i++;
	}
}

void swap_lines(char *file_name, char *line_a, char *line_b, int pos_a, int pos_b) {
	char string[MAX_LINE_LEN];
	strcpy(string, "\0");
	int curr_line = FIRST_LINE;
	//Create a new temporary file
	FILE *temp_fp = NULL;
	temp_fp = fopen("temp.txt", "w");
	//Open the original file
	FILE *fp = NULL;
	fp = fopen(file_name, "r");

	//Loop through the entire file, fp
	while (fgets(string, MAX_LINE_LEN, fp) != NULL) {
		if (curr_line == pos_a) {
			fprintf(temp_fp, "%s", line_b);
		} else if (curr_line == pos_b) {
			fprintf(temp_fp, "%s", line_a);
		} else {
			fprintf(temp_fp, "%s", string);
		}
		curr_line++;
	}

	fclose(temp_fp);
	fclose(fp);

	remove(file_name);
	//Delete the original file
	rename("temp.txt", file_name);
	//Rename the new file 'temp' to the original file
}

int file_line_num(char *file_name) {
	int line_num = 0;
	char *temp_string = malloc(MAX_LINE_LEN);
	temp_string[0] = '\0';
	FILE *fp = NULL;
	fp = fopen(file_name, "r");
		while (fgets(temp_string, MAX_LINE_LEN, fp) != NULL) {
			line_num++;
		}
	fclose(fp);
	free(temp_string);

	return line_num;
}

void sort_index(char *file_name) {
	char *line_a = malloc(MAX_LINE_LEN);
	char *line_b = malloc(MAX_LINE_LEN);
	int line_num = file_line_num(file_name);
	//Number of lines in the file

	int i, j;
	for (i = 1; i <= line_num - 1; i++) {
		FILE *fp = NULL;
		fp = fopen(file_name, "r+");
		//Open file_name for both reading and writing
		fgets(line_a, MAX_LINE_LEN, fp);
		fgets(line_b, MAX_LINE_LEN, fp);
		int pos_a = FIRST_LINE;
		int pos_b = FIRST_LINE + 1;
		for (j = 1; j <= line_num - i; j++) {
			int is_swapped = FALSE;	//Has swap_lines been executed
			//If the the first line is greater than the second line
			if (strcmp(line_a, line_b) > 0) {
				swap_lines(file_name, line_a, line_b, pos_a, pos_b);
				is_swapped = TRUE;
			}

			//Shift to the next line
			pos_a++;
			pos_b++;

			//If lines not swapped,
			//simply let line_a be line_b, and let line_b be the next line
			if (is_swapped == FALSE) {
				strcpy(line_a, line_b);
				//Shuffle along by one line
				fgets(line_b, MAX_LINE_LEN, fp);
			} else {
			//If the lines are swapped,
			//line_a remains the same, line_b is the consecutive line
				fgets(line_b, MAX_LINE_LEN, fp);
			}
		}
		fclose(fp);
	}
	free(line_a);
	free(line_b);
}
