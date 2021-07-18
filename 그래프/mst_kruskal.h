#ifndef _MST_KRUSKAL_
#define _MST_KRUSKAL_

#include "grapharrayheap.h"
#include "linkedgraph.h"
#include "linkedstack.h"

int checkCycle(LinkedGraph* graph, int fromNode, int toNode);
ArrayMinHeap* orderEdges(LinkedGraph* graph);
LinkedGraph* mstKruskal(LinkedGraph* graph);

#endif