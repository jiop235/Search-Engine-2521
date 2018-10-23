#ifndef TFIDF_H
#define TFIDF_H

#include <stdio.h>

//Function sums the tfidf values for each query term in the URL page
float tfidf_page(int pageLength, char *page_name, int argc, char **argv);

//Function returns tfidf of 'term' in 'file_name'
float tfidf_word(int pageLength, char *file_name, char *term);

//Function returns the term frequency of a term in a given file
float tf(char *term, char *file_name);

//Function returns the inverted document frequency of a term in the graph
float idf(int pageLength, char *term);

//Function returns the number of words in a given URL file
int word_count(char *file_name);

//Function returns the frequency of 'word' in a given URL file
//Frequency: number of times that the word appears in the URL file
int word_frequency(char *file_name, char *word);

//Function returns the number of URL files containing 'term', via invertedIndex.txt
int files_with_term(char *term);

//Function returns the number of words in 'string'
//Note: function assumes that 'string' has 2 leading spaces!!
int words_in_string(char *string);

char *normalise(char *string);

#endif