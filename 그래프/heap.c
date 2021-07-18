/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
	int* data;
	int maxCount;
	int currentCount;
}heap;
void displayHeap(heap* h) {
	int i = 0;
	printf("\n");
	for (i = 0; i < h->currentCount+1; i++) {
		printf(" %d", h->data[i]);
	}
}
void addMinHeap(heap *h,int data) {
	int i = 0;

	if (h->maxCount == h->currentCount) {
		printf("°¡µæÂù È÷ÇÁ!!\n");
		return;
	}
	h->currentCount++;
	i = h->currentCount;
	while ((i != 1) && (data < h->data[i / 2])) {
		h->data[i] = h->data[i / 2];
		i /= 2;
	}
	h->data[i] = data;
	printf("\n%d %d",i, h->data[i]);
	return;
}
void deleteMinHeap(heap *h) {
	int i = h->currentCount;
	int lastData = h->data[h->currentCount--];
	int child = 2, parent = 1;
	while (child < h->currentCount) {
		if ((child < h->currentCount) && h->data[child] > h->data[child+1]) {
			child++;
		}

		if (lastData <= h->data[child]) {
			break;
		}

		h->data[parent] = h->data[child];
		parent = child;
		child = child * 2;
	}
	h->data[parent] = lastData;
}

int main() {
	heap *h;
	h = (heap*)malloc(sizeof(heap));
	if (h != NULL) {
		h->maxCount = 30;
		h->currentCount = 0;
		h->data = (int*)malloc(sizeof(int)*h->maxCount);
		if (h->data != NULL) {
			h->data[0] = -1;
			addMinHeap(h,20);
			addMinHeap(h,30);
			addMinHeap(h,14);
			addMinHeap(h,39);
			addMinHeap(h,12);
			addMinHeap(h,15);
			addMinHeap(h,18);
			displayHeap(h);
			deleteMinHeap(h);
			displayHeap(h);
		}
	}

}*/