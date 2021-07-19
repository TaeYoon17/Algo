#include <stdio.h>
#include <stdlib.h>
#include "mstPrim.h"

int checkEdge(LinkedGraph* graph, int fromNodeID, int toNodeID) {
	int ret = 0;
	LinkedList* edgeList = NULL;
	LinkedListNode* edgeListNode = NULL;
	edgeList = graph->ppAdjEdge[fromNodeID];
	edgeListNode = edgeList->headerNode.next;
	while (edgeListNode != NULL) {
		if (edgeListNode->data.toNodeID == toNodeID) {
			ret = 1;
			break;
		}
		edgeListNode = edgeListNode->next;
	}
	return ret;
}
PrimGraphEdge getMinWeightEdge(LinkedGraph* graph, LinkedGraph* primMST, int fromNodeID, PrimGraphEdge Edge) {
	LinkedListNode* temp = graph->ppAdjEdge[fromNodeID]->headerNode.next;
	while (temp != NULL) {
		int weight = temp->data.weight;
		int toNodeID = temp->data.toNodeID;

		if (weight < Edge.weight) {
			int isEdgeAlready = checkEdge(primMST, fromNodeID, toNodeID);
			if (isEdgeAlready == 0) {
				int isCycle = checkCycle(primMST, fromNodeID, toNodeID);
				if (isCycle == 0) {
					Edge.fromNodeID = fromNodeID;
					Edge.toNodeID = toNodeID;
					Edge.weight = weight;
				}
			}
		}
		temp = temp->next;
	}
	return Edge;
}
LinkedGraph* mstPrim(LinkedGraph* graph, int startNodeID) {
	LinkedGraph* pReturn = NULL;
	ArrayMinHeap* heap = NULL;
	int* visited = NULL;
	int currentEdgeCount = 0, returnNodeCount = 0, graphNodeCount = graph->nodeCount;
	int i = 0;

	pReturn = createLinkedGraph(UNDIRECT_TYPE, graphNodeCount);
	visited = (int*)malloc(sizeof(int) * graph->nodeCount);
	visited[startNodeID] = 1;
	returnNodeCount = 1;
	while (graphNodeCount != returnNodeCount) {
		PrimGraphEdge Edge = { 0,0,MAX_INT };
		for (i = 0; i < graph->nodeCount; i++) {
			if (visited[i] == 1) {
				int fromNodeID = i;
				Edge = getMinWeightEdge(graph, pReturn, fromNodeID, Edge);
			}
		}
		addEdge(pReturn, Edge.fromNodeID, Edge.toNodeID, Edge.weight);
		visited[Edge.toNodeID] = 1;
		returnNodeCount++;
	}

	return pReturn;
}