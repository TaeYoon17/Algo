#ifndef _GRAPH_BFS_
#define _GRAPH_BFS_
#include "visitStack.h"
typedef struct QueueVertex {
	int* arr;
	int size;
	int head, tail;
}QueueVertex;
int isEmptyQueuVX(QueueVertex* qu);
void enqueueVX(QueueVertex* qu, int data);
int dequeueVX(QueueVertex* qu);
void traverseBFS(LinkedGraph* graph, int startVertex);
#endif