#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "List.h"
#include "tfidf.h"
#include "inverted.h"

#define FALSE 0
#define TRUE 1
#define MAX_LINE_LEN 1024
#define FIRST_LINE 1

float tfidf_page(int pageLength, char *page_name, int argc, char **argv) {
	float total_tfidf = 0;
	int i = 1;

	FILE *fp = NULL;
	if((fp = fopen(page_name, "r")) == NULL) return -1;
	char *curr_string = malloc(MAX_LINE_LEN);
	curr_string[0] = '\0';

	//For each query term
	while (i < argc) {

		int paragraph_started = FALSE;
		//Loop through the entire file, and scan each word
		while (fscanf(fp, "%s", curr_string) != EOF) {
			if (strcmp(curr_string, "Section-2") == 0) {
	 			//Section-2 has started
				paragraph_started = TRUE;
				continue;
			} else if (paragraph_started == TRUE && strcmp(curr_string, "#end") == 0) {
				//Section-2 has ended
				break;
			} 	
			//If the current query term is found in the URL file, then run tfidf_word()
			curr_string = normalise(curr_string);
			if (paragraph_started == TRUE && strcmp(curr_string, argv[i]) == 0) {
				total_tfidf += tfidf_word(pageLength, page_name, argv[i]);
			}
		}
		
		rewind(fp);
		i++;
	}

	fclose(fp);
	free(curr_string);

	return total_tfidf;
}

float tfidf_word(int pageLength, char *file_name, char *term) {
	float tfVal = tf(term, file_name);
	if(tfVal == 0) return 0;				//If not in file exit early
	return tfVal * idf(pageLength, term);
}

float tf(char *term, char *file_name) {
	int frequency = word_frequency(file_name, term);
	if(frequency == 0) return 0;		//If not in file exit early

	int doc_len = word_count(file_name);
	//Find the number of words in the file
	//Find how many times 'term' appears in the file

	float tf = (float)frequency/doc_len;
	return tf;
}

float idf(int pageLength, char *term) {
	int total_doc_num = pageLength;
	//Number of total URL files in graph
	int doc_num_with_term = files_with_term(term);
	//Number of documents containing 'term'

	return log10f((float)total_doc_num / doc_num_with_term);
}



int word_count(char *file_name) {
	int num = 0;
	FILE *fp = NULL;
	fp = fopen(file_name, "r");

	char *curr_string = malloc(MAX_LINE_LEN);
	curr_string[0] = '\0';
	int paragraph_started = FALSE;
	//Loop through the entire file, and scan each word
	while (fscanf(fp, "%s", curr_string) != EOF) {
		if (strcmp(curr_string, "Section-2") == 0) {
 		//Section-2 has started
			paragraph_started = TRUE;
			continue;
		} else if (paragraph_started == TRUE && strcmp(curr_string, "#end") == 0) {
			//Section-2 has ended
			break;
		} 	

		if (paragraph_started == TRUE) {
			num++;
		}
	}

	fclose(fp);
	free(curr_string);
	return num;
}

int word_frequency(char *file_name, char *word) {
	int frequency = 0;
	FILE *fp = NULL;
	fp = fopen(file_name, "r");

	char *curr_string = malloc(MAX_LINE_LEN);
	curr_string[0] = '\0';
	int paragraph_started = FALSE;
	//Loop through the entire file, and scan each word
	while (fscanf(fp, "%s", curr_string) != EOF) {
		if (strcmp(curr_string, "Section-2") == 0) {
 		//Section-2 has started
			paragraph_started = TRUE;
			continue;
		} else if (paragraph_started == TRUE && strcmp(curr_string, "#end") == 0) {
			//Section-2 has ended
			break;
		}
		curr_string = normalise(curr_string);
		if (paragraph_started == TRUE && strcmp(curr_string, word) == 0) {
			frequency++;
		}
	}

	fclose(fp);
	free(curr_string);
	return frequency;
}

int files_with_term(char *term) {
	FILE *fp = NULL;
	fp = fopen("invertedIndex.txt", "r");

	char *curr_string = malloc(MAX_LINE_LEN);
	curr_string[0] = '\0';
	char url_buffer[10];
	char ch;
	int file_num = 0;

	//Scan every word in invertedIndex.txt
	while (fscanf(fp, "%s", curr_string) != EOF) {
		//If fscanf has reached the line containing the inverted index of 'term'
		curr_string = normalise(curr_string);
		if (strcmp(curr_string, term) == 0) {
			//fgets() retrieves the remainder of the line, i.e. all the URLs containing 'term'
			//Note: fgets() includes 2 leading spaces that separate 'term' from the URLs
			//fgets(curr_string, MAX_LINE_LEN, fp);
			while(fscanf(fp, "%s%c", url_buffer, &ch) == 2){
					file_num++;
					if(ch == '\n') break;
				}
			break;
		}
	}
	fclose(fp);
	free(curr_string);

	return file_num;
}


