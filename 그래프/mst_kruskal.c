#include <stdio.h>
#include <stdlib.h>
#include "mst_kruskal.h"

int checkCycle(LinkedGraph* graph, int fromNode, int toNode) {
	LinkedStack* stack = NULL;
	LinkedStackNode* stackNode = NULL;
	LinkedListNode* graphListNode = NULL;
	int* visited = NULL;
	int vertexID = 0;
	int i = 0, ret = 0;

	stack = createLinkedStack();
	visited = (int*)malloc(sizeof(int) * graph->nodeCount);
	if (visited != NULL) {
		for (i = 0; i < graph->nodeCount; i++) visited[i] = 0;
		visited[fromNode] = 1;
	}
	pushLS(stack, fromNode);
	while (!isEmptyLinkedStack(stack)) {
		stackNode = popLS(stack);
		if (stackNode != NULL) {
			vertexID = stackNode->data;
			if (vertexID == toNode) {
				ret = 1;
				break;
			}
			else {
				graphListNode = graph->ppAdjEdge[vertexID]->headerNode.next;
				while (graphListNode != NULL) {
					int tempVertex = graphListNode->data.toNodeID;
					if (visited[tempVertex] == 0) {
						visited[tempVertex] = 1;
						pushLS(stack, tempVertex);
					}
					graphListNode = graphListNode->next;
				}
			}
		}
	}
	free(visited);
	free(stack);
	return ret;
}
LinkedGraph* mstKruskal(LinkedGraph* graph) {
	int i = 0, isCycle = 0, currentNodeCount = 0;
	int edgeCount = 0, * visited = NULL, currentEdgeCount = 0;

	edgeCount = graph->edgeCount;
	LinkedGraph* pReturn = createLinkedGraph(UNDIRECT_TYPE, graph->nodeCount);
	visited = (int*)malloc(sizeof(int) * graph->nodeCount);

	ArrayMinHeap* MinHeap = orderEdges(graph);
	for (i = 0; i < edgeCount; i++) {
		HeapNode* getNode = deleteMinHeapAH(MinHeap);
		isCycle = checkCycle(pReturn, getNode->data.fromNodeID, getNode->data.toNodeID);
		if (isCycle) {
			free(getNode);
		}
		else {
			addEdge(pReturn, getNode->data.fromNodeID, getNode->data.toNodeID, getNode->data.key);
			if (visited[getNode->data.fromNodeID] == 0) visited[getNode->data.fromNodeID] = 1;
			if (visited[getNode->data.toNodeID] == 0)visited[getNode->data.toNodeID] == 1;
			currentEdgeCount++;
			free(getNode);

			if (pReturn->nodeCount - 1 == currentEdgeCount) break;
		}
	}
	if (visited != NULL) free(visited);
	return pReturn;
}

ArrayMinHeap* orderEdges(LinkedGraph* graph) {
	int i = 0;
	ArrayMinHeap* pReturn = NULL;
	if (graph == NULL) {
		printf("그래프 오류\n");
		return NULL;
	}
	if (graph->edgeCount == NULL) {
		printf("간선이 없음\n");
		return NULL;
	}
	pReturn = createArrayMinHeap(graph->edgeCount);
	for (i = 0; i < graph->nodeCount; i++) {
		LinkedList* EdgeList = graph->ppAdjEdge[i];
		LinkedListNode* ListNode = EdgeList->headerNode.next;
		while (ListNode != NULL) {
			int vertexID = ListNode->data.toNodeID;
			int weight = ListNode->data.weight;
			if ((graph->graphType == DIRECT_TYPE) || (graph->graphType == UNDIRECT_TYPE && i < vertexID)) {
				GraphEdgeInfo edgeInfo = { 0, };
				edgeInfo.fromNodeID = i;
				edgeInfo.key = weight;
				edgeInfo.toNodeID = vertexID;
				insertMinHeapAH(pReturn, edgeInfo);
			}
			ListNode = ListNode->next;
		}
	}
	return pReturn;
}