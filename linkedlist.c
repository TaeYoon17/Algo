/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lindedlist.h";

LinkedList* createLinkedList() {
	LinkedList* pReturn = (LinkedList*)malloc(sizeof(LinkedList));
	memset(pReturn, 0, sizeof(LinkedList));
	return pReturn;
}
HashSlot* getLinkedListData(LinkedList* pList, int position) {
	HashSlot* pReturn = NULL;
	return pReturn;
}
int addLinkedListData(LinkedList* pList, int position, HashSlot data) {
	int ret = 0,i=0;
	LinkedListNode* pNode = NULL;
	pNode= (LinkedListNode *)malloc(sizeof(LinkedListNode));
	pNode->data = data;
	LinkedListNode* preNode = &(pList->headerNode);
	for (i = 0; i < position; i++) {
		preNode = preNode->pLink;
	}
	pNode->pLink = preNode->pLink;
	preNode->pLink = pNode;
	pList->currentCount++;
	return 1;
}
int removeLinkedListData(LinkedList* pList, int position) {
	int i = 0;
	LinkedListNode* preNode = NULL;
	LinkedListNode* DelNode = NULL;

	preNode = &(pList->headerNode);
	for (i = 0; i < position; i++) {
		preNode = preNode->pLink;
	}
	DelNode = preNode->pLink;
	preNode->pLink = DelNode->pLink;
	free(DelNode);
	pList->currentCount--;
	return 1;
}
void deleteLinkedList(LinkedList* pList) {
	LinkedListNode* preNode = NULL;
	LinkedListNode* DelNode = NULL;
	preNode = &(pList->headerNode);
	while(preNode!=NULL){
		DelNode = preNode;
		preNode = preNode->pLink;
		free(DelNode);
	}
	free(pList);
}
int getLinkedListLength(LinkedList* pList) {
	return pList->currentCount;
}*/