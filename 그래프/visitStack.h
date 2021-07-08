#ifndef _GRAPH_STACK_
#define _GRAPH_STACK_

#include "linkedgraph.h"

typedef struct StackVertex {
	int* arr;
	int size;
	int top;
}StackVX;

int FigureSameData(StackVX* stack, int node);
int isFullStack(StackVX* stack);
void pushSV(StackVX* stack, int node);
int popSV(StackVX* stack);
void traverseSV(StackVX* stack);
int getTop(StackVX* stack);

#endif