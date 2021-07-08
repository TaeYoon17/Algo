#include <stdio.h>
#include <stdlib.h>
#include "graphDFS.h";

void _traverseDFS(LinkedGraph* graph, LinkedList* list, Stack* stack) {
	int i = 0;
	printf(" %d", getTop(stack));
	if (isFullStack(stack)) return;
	for (i = 0; i < list->currentCount; i++) {
		graphEdge* temp = getLinkedListData(list, i);
		if (temp != NULL) {
			int data = temp->toNodeID;
			if (!FigureSameData(stack, data)) {
				pushSV(stack, data);
				LinkedList* next = graph->ppAdjEdge[data];
				_traverseDFS(graph, next, stack);
			}
		}
	}
	return;
}
void traverseDFS(LinkedGraph* graph, int stratVertex) {
	Stack* stack = NULL;
	stack = (Stack*)malloc(sizeof(stack));
	if (graph != NULL && stack != NULL) {
		stack->arr = (int*)malloc(sizeof(int) * (graph->nodeCount));
		stack->size = graph->nodeCount;
		stack->top = -1;
	}
	else {
		printf("할당이 잘못됨");
		return;
	}
	pushSV(stack, stratVertex);
	LinkedList* start = graph->ppAdjEdge[stratVertex];
	if (start->currentCount == 0) {
		printf("비어있는 정점\n");
	}
	else {
		printf("Start Vertex:");
		_traverseDFS(graph, start, stack);
	}
	free(stack->arr);
}
int FigureSameData(Stack* stack, int node) {
	int i = 0;
	for (i = 0; i <= stack->top; i++) {
		if (node == stack->arr[i]) return 1;
	}
	return 0;
}
int isFullStack(Stack* stack) {
	if (stack->top + 1 == stack->size) return 1;
	else return 0;
}
void pushSV(Stack* stack, int node) {
	if (FigureSameData(stack, node)) return;
	if (isFullStack(stack)) {
		printf("FullStack\n");
		return;
	}
	stack->arr[++stack->top] = node;
}
int popSV(Stack* stack) {
	int temp = -1;
	if (stack->top == -1) {
		printf("EmptyStack\n");
		return temp;
	}
	temp = stack->arr[stack->top--];
	stack->arr[stack->top + 1] = -1;
	return temp;
}
void traverseSV(Stack* stack) {
	int i = 0;
	printf("traverseSV");
	for (i = 0; i <= stack->top; i++) {
		printf("%d ", stack->arr[i]);
	}
}
int getTop(Stack* stack) {
	int temp = -1;
	temp = popSV(stack);
	pushSV(stack, temp);
	return temp;
}