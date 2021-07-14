#include <stdio.h>
#include <stdlib.h>
#include "graphDFS.h"

void _traverseDFS(LinkedGraph* graph, LinkedList* list, StackVX* stack) {
	int i = 0;
	if (isFullStack(stack)) return;
	for (i = 0; i < list->currentCount; i++) {
		graphEdge* temp = getLinkedListData(list, i);
		if (temp != NULL) {
			int data = temp->toNodeID;
			if (!FigureSameData(stack, data)) {
				printf(" Weight:%d -> %d",temp->weight,data);
				pushSV(stack, data);
				LinkedList* next = graph->ppAdjEdge[data];
				_traverseDFS(graph, next, stack);
			}
		}
	}
	return;
}
void traverseDFS(LinkedGraph* graph, int stratVertex) {
	StackVX* stack = NULL;
	stack = (StackVX*)malloc(sizeof(stack));
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
		printf("Start Vertex: %d", stratVertex);
		_traverseDFS(graph, start, stack);
	}
	free(stack->arr);
}
