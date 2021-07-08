/*#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int key;
	struct Node* next[4];
}Node;

typedef struct skipList {
	int currentCount;
	int skipLevel;
	Node* headerNode;
}skipList;

Node* getnode() {
	Node* node = NULL;
	int i = 0;
	node = (Node*)malloc(sizeof(Node));
	node->key = 0;
	for (i = 0; i < 4; i++) {
		node->next[i] = NULL;
	}
	return node;
}

skipList createSkipList() {
	skipList skip = {0,};
	skip.currentCount = 0; skip.skipLevel = 4;
	skip.headerNode = getnode();
	return skip;
}
Node* searchNode(skipList *list,int key) {
	int level=list->skipLevel-1;
	Node* node = list->headerNode;
	Node* pReturn = NULL;
	int flag;
	flag=_findNode(level,0,&node,key);
	if (flag != 1) {
		printf("같은 데이터가 없습니다. 오류!\n");
		pReturn = NULL;
	}
	else pReturn = node;
	return pReturn;
}
void addNode(skipList *list,int key,int size) {
	int level = list->skipLevel - 1;
	Node* tempNode=NULL;
	Node* newNode = getnode();
	newNode->key = key;
	int i = 0,flag=0;
	for (i = 0; i < size&&flag==0; i++) {
		level = list->skipLevel - 1;
		tempNode = list->headerNode;
		flag = _findNode(level,i,&(tempNode),key);
		if (flag==0) {
			newNode->next[i] = tempNode->next[i];
			tempNode->next[i] = newNode;
		}
		else {
			printf("같은 노드가 이미 있음!!\n");
			return;
		}
	}
}
int _findNode(int level,int index,Node** node,int key) {
	int currentLevel=level;
	int ret = 0;
	while (currentLevel >index-1) {
		if ((*node)->next[currentLevel] == NULL) currentLevel--;
		else {
			if ((*node)->next[currentLevel]->key < key) {
				(*node) = (*node)->next[currentLevel];
				currentLevel = level;
			}
			else if ((*node)->next[currentLevel]->key > key) currentLevel--;
			else {
				(*node) = (*node)->next[currentLevel];
				ret = 1;
				break;
			}
		}
	}
	return ret;
}

void removeNode(skipList *list,int key) {
	int i = 0,flag=0,level=0;
	Node* removeNode = searchNode(list, key);
	if (removeNode == NULL) {
		printf("찾기 오류!\n");
		return;
	}
	Node* tempNode = NULL;
	for (i = 0; i < list->skipLevel; i++) {
		tempNode = list->headerNode;
		while (tempNode->next[i] != NULL && tempNode->next[i] != removeNode) {
			tempNode = tempNode->next[i];
		}
		if (tempNode->next[i] == removeNode) {
			tempNode->next[i] = removeNode->next[i];
		}
	}
	free(removeNode);
}
void displayList(skipList skip) {
	Node* node = skip.headerNode;
	Node* temp = NULL;
	int i = 0;
	for (i = 0; i < 4; i++) {
		temp = node->next[i];
		printf("floor %d:", i + 1);
		while (temp != NULL) {
			printf("%d ", temp->key);
			temp = temp->next[i];
		}
		printf("\n");
	}
}
int main() {
	skipList skip = createSkipList();
	addNode(&skip, 3,1);
	addNode(&skip, 6,4);
	addNode(&skip, 1, 4);
	addNode(&skip, 2, 3);
	addNode(&skip, 6, 3);
	displayList(skip);
	removeNode(&skip,3);
	displayList(skip);
}
*/