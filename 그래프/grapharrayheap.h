#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct GraphEdgeInfoType
{
    int key;
    int fromNodeID;
    int toNodeID;
} GraphEdgeInfo;

typedef struct HeapNodeType
{
    GraphEdgeInfo data;
} HeapNode;

typedef struct ArrayHeapType
{
    int maxCount;           // �ִ� ��� ����
    int currentCount;       // ���� ��� ����
    HeapNode *pData;		// ��� ������ ���� 1���� array
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* createArrayMaxHeap(int maxCount);
int insertMaxHeapAH(ArrayMaxHeap* pHeap, GraphEdgeInfo value);
HeapNode* deleteMaxHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayMaxHeap(ArrayMaxHeap* pHeap);

ArrayMaxHeap* createArrayMinHeap(int maxCount);
int insertMinHeapAH(ArrayMaxHeap* pHeap, GraphEdgeInfo value);
HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayMinHeap(ArrayMaxHeap* pHeap);

void displayArrayHeap(ArrayMaxHeap* pHeap);

#endif
