#ifndef _LINKED_STACK_
#define _LINKED_STACK_

typedef struct LinkedStackNodeType {
	int data;
	struct LinkedStackNodeType* next;
}LinkedStackNode;

typedef struct LinkedStackType {
	int currentCount;
	LinkedStackNode* top;
}LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* stack, int data);
int isEmptyLinkedStack(LinkedStack* stack);
LinkedStackNode* popLS(LinkedStack* stack);
LinkedStackNode* peekLS(LinkedStack* stack);
void deleteLinkedStack(LinkedStack* stack);
void displayLinkedStack(LinkedStack* stack);
#endif