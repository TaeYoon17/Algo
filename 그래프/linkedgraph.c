#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph.h";

LinkedGraph* createLinkedGraph(int type, int size) {
	LinkedGraph* pReturn = NULL;
	int i;
	if (size <= 0) {
		printf("크기는 0보다 커야한다!!\n");
		return NULL;
	}
	else {
		pReturn = (LinkedGraph*)malloc(sizeof(LinkedGraph));
		if (pReturn == NULL) {
			printf("linkedGraph 동적할당 오류!!\n");
			return NULL;
		}
		pReturn->graphType = type;
		pReturn->nodeCount = size;
	}
	pReturn->ppAdjEdge = (LinkedList**)malloc(sizeof(LinkedList*) * size);
	if (pReturn->ppAdjEdge == NULL) {
		printf("ppAdgEdge 동적할당 오류!!\n");
		if (pReturn != NULL)free(pReturn);
		return NULL;
	}
	for (i = 0; i < size; i++) {
		pReturn->ppAdjEdge[i] = createLinkedList();
		if (pReturn->ppAdjEdge[i] == NULL) {
			printf("LinkedList 메모리 할당 오류!!\n");
			if (pReturn->ppAdjEdge != NULL) free(pReturn->ppAdjEdge);
			if (pReturn != NULL) free(pReturn);
			return NULL;
		}
	}
	return pReturn;
}
int checkVertexValid(LinkedGraph* graph, int node) {
	int ret = 0;
	if (graph != NULL && 0 <= node && node < graph->nodeCount) ret = 1;
	return ret;
}

int addEdgeInternal(LinkedGraph* graph, int fromNode, int toNode, int weight) {
	int ret = 0;
	if (checkVertexValid(graph, fromNode) && checkVertexValid(graph, toNode)) {
		graphEdge data;
		data.toNodeID = toNode;
		data.weight = weight;
		addLinkedListData(graph->ppAdjEdge[fromNode], 0, data);
	}
	else {
		ret = -1;
	}
	return ret;
}
int removeEdgeInternal(LinkedGraph* graph, int fromNode, int toNode) {
	int ret = 0, i = 0;
	LinkedList* tempList = NULL;
	graph->ppAdjEdge[fromNode];
	if (checkVertexValid(graph, fromNode) && checkVertexValid(graph, toNode)) {
		tempList = graph->ppAdjEdge[fromNode];
		if (tempList == NULL) {
			printf("해당 리스트는 없음...\n");
			ret = -1;
			return ret;
		}
		for (i = 0; i < tempList->currentCount; i++) {
			graphEdge* currentEdge = getLinkedListData(tempList, i);
			if (tempList != NULL && currentEdge->toNodeID == toNode) {
				removeLinkedListData(tempList, i);
				ret = 0;
				break;
			}
		}
	}
	else ret = -1;
	return ret;
}
int addEdge(LinkedGraph* graph, int fromNode, int toNode, int weight) {
	int ret = 0;
	ret = addEdgeInternal(graph, fromNode, toNode, weight);
	if (ret == 0 && graph->graphType == UNDIRECT_TYPE) {
		ret = addEdgeInternal(graph, toNode, fromNode, weight);
	}
	return ret;
}
int removeEdge(LinkedGraph* graph, int fromNode, int toNode) {
	int ret = 0;
	ret = removeEdgeInternal(graph, fromNode, toNode);
	if (ret == 0 && graph->graphType == 1) {
		ret = removeEdgeInternal(graph, toNode, fromNode);
	}
	return ret;
}