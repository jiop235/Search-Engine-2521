#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>

typedef struct URLNode {
	char *string;
	struct URLNode *next;
} URLNode;

typedef struct URLList {
	URLNode *first;
	URLNode *last;
} URLList;

//Create invertedindex.txt with the inverted index of the graph
void invertedIndex(Graph g);

//Function normalises and returns the input string
char *normalise(char *string);

//Function returns true if the word has been encountered before, otherwise, function returns false
int word_encountered(URLList *words, char *string);

//Find occurrences of curr_string in all of the urls, and note the relevant urls in inverted.txt
void find_and_insert(Graph g, char *string);

//Function returns the number of lines in a given file
int file_line_num(char *file_name);

//Function swaps two lines in the file, given the two lines and their line numbers
void swap_lines(char *file_name, char *line_a, char *line_b, int pos_a, int pos_b);

//Function applied bubble sort to sort the lines of invertedIndex.txt in ascending order
void sort_index(char *file_name);

#endif
