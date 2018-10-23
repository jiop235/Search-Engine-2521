
#ifndef RANK_LIST
#define RANK_LIST


typedef struct _rankNode{
	int nLines;
	char **list;
	char *urlName;
	struct _rankNode *next;
}*rankNode;


typedef struct _rankList{
	int nLists;
	rankNode first;
}*rankList;

//Create empty rankList
rankList createRankList();

//Insert List into rankList;
void insertRankNode(rankList L, char **List, int size, char *urlName);

//free rankList
void freeRankList(rankList L);

void showRankList(rankList L);

#endif