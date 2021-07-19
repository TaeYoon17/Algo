#ifndef _MST_PRIM_
#define _MST_PRIM_

#include "linkedgraph.h"
#include "grapharrayheap.h"

typedef struct PrimGraphEdgeType {
	int fromNodeID;
	int toNodeID;
	int weight;
}PrimGraphEdge;

int checkEdge(LinkedGraph* graph, int fromNodeID, int toNodeID);
PrimGraphEdge getMinWeightEdge(LinkedGraph* graph, LinkedGraph* primMST, int fromNodeID, PrimGraphEdge Edge);

#endif