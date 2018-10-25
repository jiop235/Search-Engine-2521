#define _SVID_SOURCE
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "inverted.h"

#define TRUE 1
#define FALSE 0
#define MAX_WORD_LEN 128


int main () {
	//Retrieve an array including all the URL file names
	int collection_size = collectionLength("collection.txt");
	char **collection = getCollection("collection.txt",  collection_size);

	//Create a new tree
	Tree t = NULL;

	//Loop through each URL file
	int i;
	for (i = 0; i < collection_size; i++) {
		char *url_txt = append_txt(collection[i]);
		FILE *fp = NULL;
		fp = fopen(url_txt, "r");
			//Loop through each word in the URL file
			char *buffer = malloc(MAX_WORD_LEN);
			buffer[0] = '\0';
			int paragraph_started = FALSE;	//Whether fscanf has scanned into the paragraph of words

			while (fscanf(fp, "%s", buffer) != EOF) {
			 	if (strcmp(buffer, "Section-2") == 0) {
		 		//Section-2 has started
	 				paragraph_started = TRUE;
	 				continue;
	 			} else if (paragraph_started == TRUE && strcmp(buffer, "#end") == 0) {
	 			//Section-2 has ended
	 				break;
	 			}

	 			//fscanf is scanning the words in Section-2
	 			if (paragraph_started == TRUE) {
					//Normalise the word
					buffer = normalise(buffer);
					//Search for 'buffer' in the tree
					Tree matching_node = TreeSearch(t, buffer);
					//If the word is not found in the tree
					if (matching_node == NULL) {
						t = insertAtLeaf(t, buffer);
						//Insert a new treeNode into the tree containing the word
						matching_node = TreeSearch(t, buffer);
						//Search for the treeNode that was inserted
					}
					matching_node->URLList = insertListNode(matching_node->URLList, collection[i]);
					//Append the URL in which the word is from to the linked list of that word
				}
			}

			free(buffer);
			free(url_txt);
		fclose(fp);
	}

	//Print the constructed BST into invertedIndex.txt

	//Create the file invertedIndex.txt
	FILE *inverted_fp = NULL;
	inverted_fp = fopen("invertedIndex.txt", "w");
	
		print_BST(t, inverted_fp);

	fclose(inverted_fp);

	return 0;
}

//===============BST TREE ADT FUNCTIONS===============

Tree newTreeNode(char *item) {
	Tree new = malloc(sizeof(treeNode));
	new->word = strdup(item);
	//Note: strdup() allocates memory for new->word
	new->URLList = NULL;
	new->left = NULL;
	new->right = NULL;

	return new;
}

Tree TreeSearch(Tree t, char *item) {
	//Traverse through the tree using recursion
	if (t == NULL) {
		return NULL;
	} else if (strcmp(item, t->word) < 0) {
		return TreeSearch(t->left, item);
	} else if (strcmp(item, t->word) > 0) {
		return TreeSearch(t->right, item);
	} else {
	//If 'key' for the node is 'item'
		return t;
		//Return the pointer to the tree node with 'key' == 'item'
	}
}

Tree insertAtLeaf(Tree t, char *item) {
	//If tree is empty
	if (t == NULL) {
		t = newTreeNode(item);
		//Return tree with only the new node
	} else if (strcmp(item, t->word) < 0) {
	//If 'item' is less than 'word' in the current node
		t->left = insertAtLeaf(t->left, item);
		//Return the new tree after insertion is complete
	} else if (strcmp(item, t->word) > 0) {
	//If 'item' is greater than 'word' in the current node
		t->right = insertAtLeaf(t->right, item);
	}

	return t;
	//If item is already in the tree, i.e. strcmp() == 0
	//Simply return the unaltered tree, to avoid duplicates
}

//===============Linked List ADT FUNCTIONS===============

listNode *newListNode(char *string) {
	listNode *new = malloc(sizeof(listNode));
	new->URL_name = strdup(string);
	new->next = NULL;

	return new;
}

int StringInList(listNode *list, char *string) {
	listNode *curr = list;
	while (curr != NULL) {
		//If string equals URL_name of a node in linked list
		if (strcmp(curr->URL_name, string) == 0) {
			return TRUE;
		}
		curr = curr->next;
	}

	return FALSE;
}

listNode *insertListNode(listNode *list, char *string) {
	listNode *head = list;
	//If 'string' is not found in the list, insert at tail
	if (StringInList(list, string) == FALSE) {
		listNode *new = newListNode(string);
		listNode *curr = head;
		//If list is empty
		if (head == NULL) {
			head = new;
		} else {
			//Loop to the tail of the list
			while (curr->next != NULL) {
				curr = curr->next;
			}

			curr->next = new;
		}
	}

	return head;
}

//======================================================

char *append_txt(char *string) {
		char *string_txt = malloc(strlen(string) + strlen(".txt") + 1);
		string_txt[0] = '\0';
 		strcat(string_txt, string);
 		strcat(string_txt, ".txt");
 		//Append '.txt' at the end of curr_url
 		return string_txt;
}

void print_BST(Tree t, FILE *inverted_fp) {
	//Traverse through the tree using infix order, using recursion
	if (t == NULL) {
	} else {
		print_BST(t->left, inverted_fp);

		fprintf(inverted_fp, "%s ", t->word);
		print_URLList(t->URLList, inverted_fp);
		fprintf(inverted_fp, "\n");

		print_BST(t->right, inverted_fp);
	}
}

void print_URLList(listNode *list, FILE *inverted_fp) {
	//Loop through the entire list
	listNode *curr = list;
	while (curr != NULL) {
		fprintf(inverted_fp, " %s", curr->URL_name);

		curr = curr->next;
	}
}