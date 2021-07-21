#include <stdio.h>
#include <stdlib.h>
#include "arrayheap.h"

ArrayMinHeap* createArrayHeap(int count) {
	ArrayMinHeap* pReturn = NULL;
	pReturn = (ArrayMinHeap*)malloc(sizeof(ArrayMinHeap));
	if (pReturn != NULL) {
		pReturn->maxCount = count;
		pReturn->pData = (HeapNode*)malloc(sizeof(HeapNode) * (count + 1));
		pReturn->currentCount = 0;
	}
	else {
		printf("赛 积己 坷幅!!");
	}
	return pReturn;
}
void appendMinHeap(ArrayMinHeap* minHeap, HeapNode node) {
	if (minHeap->maxCount == minHeap->currentCount) {
		printf("赛 侩樊 弥措\n");
		return;
	}
	else {
		minHeap->currentCount++;
		int i = minHeap->currentCount;
		minHeap->pData[i] = node;
		while (1 < i) {
			if (minHeap->pData[i].frequency < minHeap->pData[i / 2].frequency) {
				HeapNode temp = minHeap->pData[i];
				minHeap->pData[i] = minHeap->pData[i / 2];
				minHeap->pData[i / 2] = temp;
			}
			else break;
			i /= 2;
		}
	}
}
void displayMinHeap(ArrayMinHeap* minHeap) {
	int i = 0;
	for (i = 0; i <= minHeap->currentCount; i++) {
		printf("i: %d -> %d ", i, minHeap->pData[i].frequency);
	}
}
HeapNode* deleteMinHeap(ArrayMinHeap* minHeap) {
	HeapNode* pReturn = NULL;
	HeapNode* temp = NULL;
	if (minHeap->currentCount > 0) {
		pReturn = (HeapNode*)malloc(sizeof(HeapNode));
		int parentIdx = 1, childrenIdx = 2;
		*pReturn = minHeap->pData[parentIdx];
		temp = &(minHeap->pData[minHeap->currentCount]);
		minHeap->currentCount--;
		while (childrenIdx <= minHeap->currentCount) {
			if ((childrenIdx < minHeap->currentCount) &&
				(minHeap->pData[childrenIdx].frequency > minHeap->pData[childrenIdx + 1].frequency)) {
				childrenIdx++;
			}
			if (temp->frequency < minHeap->pData[childrenIdx].frequency) {
				break;
			}
			minHeap->pData[parentIdx] = minHeap->pData[childrenIdx];
			parentIdx = childrenIdx;
			childrenIdx = childrenIdx * 2;
		}
		minHeap->pData[parentIdx] = *temp;
	}
	return pReturn;
}