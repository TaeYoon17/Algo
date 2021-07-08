#ifndef _GRAPH_DFS_
#define _GRPAH_DFS_

#include "linkedgraph.h";

typedef struct StackVertex {
	int* arr;
	int size;
	int top;
}Stack;

void _traverseDFS(LinkedGraph* graph, LinkedList* list, Stack* stack);
void traverseDFS(LinkedGraph* graph, int stratVertex);
int FigureSameData(Stack* stack, int node);
int isFullStack(Stack* stack);
void pushSV(Stack* stack, int node);
int popSV(Stack* stack);
void traverseSV(Stack* stack);
int getTop(Stack* stack);
#endif