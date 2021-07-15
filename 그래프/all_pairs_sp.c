#include <stdio.h>
#include <stdlib.h>
#include "all_pairs_sp.h"

void displayFloyd(int** AllDistance, int nodeCount) {
	int i = 0, j = 0;
	for (i = 0; i < nodeCount; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	for (i = 0; i < nodeCount; i++) {
		printf("%d: ", i);
		for (j = 0; j < nodeCount; j++) {
			printf("\t%d", AllDistance[i][j]);
		}
		printf("\n");
	}
}

int** PathFloyd(LinkedGraph* graph) {
	int** AllDistance = NULL;
	int** AllS = NULL;
	int nodeCount = 0, i = 0, j = 0, k = 0;
	int temp = 0;
	if (graph == NULL) {
		printf("그래프 오류!!\n");
	}
	nodeCount = graph->nodeCount;
	AllDistance = (int**)calloc(sizeof(int*), nodeCount);
	if (AllDistance == NULL) {
		printf("동적할당 오류!!\n");
		return NULL;
	}
	for (i = 0; i < nodeCount; i++) {
		AllDistance[i] = (int*)calloc(sizeof(int), nodeCount);
		if (AllDistance[i] == NULL) {
			for (j = 0; j < i - 1; j++) {
				if (AllDistance[j] != NULL) free(AllDistance[j]);
			}
			if (AllDistance != NULL) free(AllDistance);
			return NULL;
		}
	}
	for (i = 0; i < nodeCount; i++) {
		for (j = 0; j < nodeCount; j++) {
			if (i == j) {
				AllDistance[i][j] = 0;
			}
			else {
				graphEdge* Edge = getEdge(graph, i, j);
				if (Edge != NULL) AllDistance[i][j] = Edge->weight;
				else AllDistance[i][j] = MAX_INT;
			}
		}
	}

	displayFloyd(AllDistance, nodeCount);
	printf("\n");
	for (i = 0; i < nodeCount; i++) {
		for (j = 0; j < nodeCount; j++) {
			for (k = 0; k < nodeCount; k++) {
				temp = AllDistance[j][i] + AllDistance[i][k];
				if (temp < AllDistance[j][k]) {
					AllDistance[j][k] = temp;
				}
			}
		}
		printf("%d번째 중간노드\n", i);
		displayFloyd(AllDistance, nodeCount);
	}
	return NULL;
}