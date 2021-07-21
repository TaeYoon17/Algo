#ifndef _ARRAY_HEAP
#define _ARRAY_HEAP


typedef struct HeapNodeType {
	int frequency;
	void* pData;
}HeapNode;
typedef struct HeapTreeType {
	int maxCount;
	int currentCount;
	HeapNode* pData;
}ArrayMaxHeap, ArrayMinHeap;

ArrayMinHeap* createArrayHeap(int count);
void appendMinHeap(ArrayMinHeap* minHeap, HeapNode node);
void displayMinHeap(ArrayMinHeap* minHeap);
HeapNode* deleteMinHeap(ArrayMinHeap* minHeap);
#endif