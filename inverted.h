#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>

typedef struct listNode {
	char *URL_name;
	struct listNode *next;
} listNode;

typedef struct treeNode *Tree;

struct treeNode {
	char *word;			//Key
	listNode *URLList;	//Linked list of URLS in which the key is found in
	Tree left;			//Pointer to left child
	Tree right;			//Pointer to right child
} treeNode;

//Function creates a new TreeNode containing the string 'item'
Tree newTreeNode(char *item);

//Function searches through the given tree 't' for the string 'item'
//If present, function returns a pointer to the node containing 'item'
//If not present, function returns NULL
Tree TreeSearch(Tree t, char *item);

//Function inserts a node at the leaf of tree 't', containing the string 'item'
//Note: function maintains the structure of a BST after insertion
Tree insertAtLeaf(Tree t, char *item);

//Function creates a new list node containing 'string'
listNode *newListNode(char *string);

//Function returns if 'string' is present in the list
int StringInList(listNode *list, char *string);

//Function inserts the string into the given linked list at the tail,
//and returns the head of the new linked list
//Note: If 'string' is already present in the linked list,
//the function will not insert a duplicate
//Note: Function creates a new listNode containing 'string'
listNode *insertListNode(listNode *list, char *string);


//Function appends '.txt' to the end of a string
char *append_txt(char *string);

//Function prints out the BST in infix order
//Format: <treeNode->word>  <treeNode->URLList> <treeNode->URLList->next>...
void print_BST(Tree t, FILE *inverted_fp);

//Function prints out the given linked list into file with file pointer 'inverted_fp'
void print_URLList(listNode *list, FILE *inverted_fp);

#endif