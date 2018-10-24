
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

char** getUniqueList(rankList L, char **list);

//Get total amount of urls in all lists
int getTotalCardinality(rankList L);

//Get cardinality for url given
int getCardinality(rankList L, char *url);


float bruteForce(rankList L, int level, float low, char** finalList);

void swap(rankList L, int a);

#endif