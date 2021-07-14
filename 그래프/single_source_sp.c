#include <stdio.h>
#include <stdlib.h>
#include "single_source_sp.h"

void printDistanceInfo(int startVertex, int Distance[], int nodeCount) {
	int i = 0;
	for (i = 0; i < nodeCount; i++) {
		if (i != startVertex) {
			printf("%d: %d\n", i, Distance[i]);
		}
	}
}
int getMinDisatance(int Distance[], int S[], int nodeCount) {
	int i = 0, temp = MAX_INT, ret = -1;
	for (i = 0; i < nodeCount; i++) {
		if (S[i] == 1 && temp > Distance[i]) {
			temp = Distance[i];
			ret = i;
		}
	}
	return ret;
}

int* PathDijkstra(LinkedGraph* graph, int startVertex) {
	int* Distance = NULL;
	int* S = NULL;
	int nodeCount = 0, i = 0;
	int vNodeID = 0, y_w, y_v;

	nodeCount = graph->nodeCount;
	Distance = (int*)malloc(sizeof(int) * nodeCount);
	S = (int*)malloc(sizeof(int) * nodeCount);
	printf("초기화\n");
	if (Distance != NULL && graph != NULL && S != NULL) {
		for (i = 0; i < nodeCount; i++) {
			S[i] = 1;
			graphEdge* data = getEdge(graph, startVertex, i);
			if (data != NULL) {
				Distance[i] = data->weight;
			}
			else {
				Distance[i] = MAX_INT;
			}
		}
		Distance[startVertex] = 0;
		S[startVertex] = 0;
	}
	printDistanceInfo(startVertex, Distance, nodeCount);

	for (i = 0; i < nodeCount - 1; i++) {
		printf("\n%d번째 루프\n",i+1);
		int vNodeID = getMinDisatance(Distance, S, nodeCount);
		S[vNodeID] = 0;
		LinkedList* wNode = graph->ppAdjEdge[vNodeID];
		if (wNode != NULL) {
			LinkedListNode* edgeNode = wNode->headerNode.next;
			while (edgeNode != NULL) {
				int wNodeID = edgeNode->data.toNodeID;
				int c_v_w = edgeNode->data.weight;
				y_w = Distance[wNodeID];
				y_v = Distance[vNodeID];
				int sum = c_v_w + y_v;
				if (sum < y_w) {
					Distance[wNodeID] = sum;
					printf("\t %d 노드의 이전 노드는 %d로 변경, 거리는 %d에서 %d로 감소\n",
						wNodeID, vNodeID, y_w, sum);
				}
				edgeNode = edgeNode->next;
			}
		}
		printDistanceInfo(startVertex, Distance, nodeCount);
	}
	free(S);
	return Distance;
}