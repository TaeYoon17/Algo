#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h";

LinkedList* createLinkedList() {
	LinkedList* pReturn = NULL;
	pReturn = (LinkedList*)malloc(sizeof(LinkedList));
	if (pReturn == NULL) {
		printf("LinkedList ���� ����!!\n");
		return NULL;
	}
	memset(pReturn, 0, sizeof(LinkedList));
	pReturn->headerNode.data.toNodeID = -1;
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
		printf("������ �ֽ��ϴ�!\n");
		return -1;
	}
	newNode->data = data;
	while (currentNode->next != NULL&&currentNode->next->data.toNodeID<data.toNodeID) {
		currentNode = currentNode->next;
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

void deleteLinkedList(LinkedList* pList) {
	LinkedListNode* pDelNode = NULL;
	LinkedListNode* pPreNode = pList->headerNode.next;
	while (pPreNode != NULL) {
		pDelNode = pPreNode;
		pPreNode = pPreNode->next;
		free(pDelNode);
	}

	free(pList);
}