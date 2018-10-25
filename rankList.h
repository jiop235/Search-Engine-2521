
#ifndef RANK_LIST
#define RANK_LIST


typedef struct _rankNode{
	int nLines;
	char **list;
	char *urlName;
	struct _rankNode *next;
}*rankNode;

typedef struct _uniqueNode{
	int index;
	char *urlName;
	struct _uniqueNode *next;
}*uniqueNode;

typedef struct _rankList{
	int nLists;
	rankNode first;
	int nUnique;
	uniqueNode uFirst;
	uniqueNode uLast;
}*rankList;



//Create empty rankList
rankList createRankList();

//Insert List into rankList;
void insertRankNode(rankList L, char **List, int size, char *urlName);

void insertUniqueNode(rankList L, int index, char *urlName);

int UniquePos(char *searchURL, uniqueNode first);

int getRankPos(char *searchURL, int size, char **array);

//free rankList
void freeRankList(rankList L);

//show rankList
void showRankList(rankList L);

//Get the number of lists
int getNumberLists(rankList L);

//Loop through unique and put in an array
char** getUniqueList(rankList L, char **list);

//Brute force recursion
float bruteForce(rankList L, int level, float low, char** finalList);

//Swap tbetween two nodes values
void swap(rankList L, int a);

#endif