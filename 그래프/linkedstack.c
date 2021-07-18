#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

LinkedStack* createLinkedStack() {
	LinkedStack* pReturn = NULL;
	pReturn = (LinkedStack*)malloc(sizeof(LinkedStack));
	if (pReturn == NULL) {
		printf("fail to createLinkedStack\n");
		return NULL;
	}
	else {
		pReturn->currentCount = 0;
		memset(pReturn, 0, sizeof(LinkedStack));
	}
	return pReturn;
}
int pushLS(LinkedStack* stack, int data) {
	LinkedStackNode* Node = NULL;
	int ret = 0;
	if (stack != NULL) {
		Node = (LinkedStackNode*)malloc(sizeof(LinkedStackNode));
		if (Node != NULL) {
			Node->data = data;
			Node->next = stack->top;
			stack->top = Node;
			stack->currentCount++;
			ret = 1;
		}
	}
	else {
		printf("노드 오류!!\n");
	}
	return ret;
}
int isEmptyLinkedStack(LinkedStack* stack) {
	return stack != NULL && stack->currentCount == 0 ? 1 : 0;
}
LinkedStackNode* popLS(LinkedStack* stack) {
	LinkedStackNode* pReturn = NULL;
	if (!isEmptyLinkedStack(stack)) {
		pReturn = stack->top;
		stack->top = pReturn->next;
		pReturn->next = NULL;
		stack->currentCount--;
	}
	return pReturn;
}
LinkedStackNode* peekLS(LinkedStack* stack) {
	LinkedStackNode* pReturn = NULL;
	if (!isEmptyLinkedStack(stack)) {
		pReturn = stack->top;
	}
	return pReturn;
}
void deleteLinkedStack(LinkedStack* stack) {
	LinkedStackNode* Node = NULL;
	LinkedStackNode* temp = NULL;
	if (stack != NULL) {
		Node = stack->top;
		while (Node != NULL) {
			temp = Node;
			Node = Node->next;
			free(temp);
		}
		free(stack);
	}
}
void displayLinkedStack(LinkedStack* stack) {
	LinkedStackNode* Node = NULL;
	if (stack != NULL) {
		Node = stack->top;
		while (Node != NULL) {
			printf("%d ", Node->data);
			Node = Node->next;
		}
	}
}