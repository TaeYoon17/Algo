#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h";

LinkedList* createLinkedList() {
	LinkedList* pReturn = NULL;
	pReturn = (LinkedList*)malloc(sizeof(LinkedList));
	if (pReturn == NULL) {
		printf("LinkedList 선언 오류!!\n");
		return NULL;
	}
	memset(pReturn, 0, sizeof(LinkedList));
	return pReturn;
}

graphEdge* getLinkedListData(LinkedList* list, int position) {
	graphEdge* ret = NULL;
	int i = 0;

	LinkedListNode* currentNode = &(list->headerNode);
	for (i = 0; i <= position; i++) {
		currentNode = currentNode->next;
	}
	if (currentNode != NULL) {
		ret = &(currentNode->data);
	}
	return ret;
}

int addLinkedListData(LinkedList* list, int position, graphEdge data) {
	LinkedListNode* currentNode = &(list->headerNode);
	LinkedListNode* newNode = NULL;
	int i = 0;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (newNode == NULL) {
		printf("오류가 있습니다!\n");
		return -1;
	}
	newNode->data = data;
	for (i = 0; i < position; i++) {
		graphEdge tempData = currentNode->data;
		if (tempData.toNodeID == data.toNodeID) {
			printf("같은 노드 방향 간선이 이미 존재함!");
			return -1;
		}
		currentNode = currentNode->next;
	}
	graphEdge tempData = currentNode->data;
	if (tempData.toNodeID == data.toNodeID) {
		printf("같은 노드 방향 간선이 이미 존재함!");
		return -1;
	}
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	list->currentCount++;
	return 1;
}
int removeLinkedListData(LinkedList* list, int position) {
	LinkedListNode* preNode = &(list->headerNode);
	LinkedListNode* delNode = NULL;
	int i = 0;
	for (i = 0; i < position; i++) preNode = preNode->next;
	delNode = preNode->next;
	preNode->next = delNode->next;
	free(delNode);
	list->currentCount--;
	return 1;
}