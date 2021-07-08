#include <stdio.h>
#include <stdlib.h>
#include "graphBFS.h"

int isEmptyQueuVX(QueueVertex* qu) {
	if (qu->head == qu->tail) return 1;
	else return 0;
}
void enqueueVX(QueueVertex* qu, int data) {
	int temp = (qu->tail + 1) % qu->size;
	if (temp == qu->head) {
		printf("FULL!!\n");
		return;
	}
	else {
		qu->tail = temp;
		qu->arr[temp] = data;
	}
}
int dequeueVX(QueueVertex* qu) {
	int ret = 0;
	if (isEmptyQueuVX(qu)) {
		printf("isEmpty\n");
	}
	else {
		ret = qu->arr[qu->head + 1];
		qu->arr[qu->head] = -1;
		qu->head = qu->head + 1 % qu->size;
	}
	return ret;
}

void traverseBFS(LinkedGraph* graph, int startVertex) {
	StackVX* stack = NULL;
	stack = (StackVX*)malloc(sizeof(stack));
	QueueVertex* qu = (QueueVertex*)malloc(sizeof(QueueVertex));
	int i = 0;
	if (graph != NULL && stack != NULL && qu != NULL) {
		int count = graph->nodeCount;
		stack->arr = (int*)malloc(sizeof(int) * count);
		stack->size = count;
		stack->top = -1;
		qu->arr = (int*)malloc(sizeof(int) * (count + 1));
		qu->size = count + 1;
		qu->head = 0; qu->tail = 0;
	}
	else {
		printf("할당이 잘못됨");
		return;
	}
	pushSV(stack, startVertex);
	int vx = startVertex;
	LinkedList* list = graph->ppAdjEdge[vx];
	if (list != NULL) {
		printf("Start Vertex: %d", vx);
		do {
			list = graph->ppAdjEdge[vx];
			for (i = 0; i < list->currentCount; i++) {
				graphEdge* temp = getLinkedListData(list, i);
				if (temp != NULL) {
					int data = temp->toNodeID;
					if (!FigureSameData(stack, data)) {
						printf(" %d", data);
						pushSV(stack, data);
						enqueueVX(qu, data);
					}
				}
			}
			vx = dequeueVX(qu);
		} while (!isFullStack(stack));
	}
	else {
		printf("해당 리스트는 데이터가 없음\n");
	}
}
