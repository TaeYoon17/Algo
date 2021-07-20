#include <stdio.h>
#include <stdlib.h>
#define MAX_BIT_SIZE 8
#define COUNT_ASC 128

typedef struct HeapNodeType {
	int frequency;
	void* pData;
}HeapNode;
typedef struct HeapTreeType{
	int maxCount;
	int currentCount;
	HeapNode* pData;
}ArrayMaxHeap,ArrayMinHeap;

typedef struct HuffmanTreeNodeType {
	char data;
	char bitString[MAX_BIT_SIZE + 1];
	struct HuffmanTreeNodeType* left;
	struct HuffmanTreeNodeType* right;
}HuffmanTreeNode;
typedef struct HuffmanTreeType {
	HuffmanTreeNode* root;
}HuffmanTree;

typedef struct HuffmanCodeType {
	char data;
	int frequency;
	char bitString[MAX_BIT_SIZE + 1];
}HuffmanCode;
typedef struct HuffmanCodeTableType {
	HuffmanCode* idx;
}HuffmanCodeTable;

ArrayMinHeap* createArrayHeap(int count) {
	ArrayMinHeap* pReturn = NULL;
	pReturn = (ArrayMinHeap*)malloc(sizeof(ArrayMinHeap));
	if (pReturn != NULL) {
		pReturn->maxCount = count;
		pReturn->pData = (HeapNode*)malloc(sizeof(HeapNode)*(count+1));
		pReturn->currentCount = 0;
	}
	else {
		printf("赛 积己 坷幅!!");
	}
	return pReturn;
}
int isEmptyHeap(ArrayMinHeap *heap){}
void appendMinHeap(ArrayMinHeap *heap,HeapNode node) {
	if (heap->maxCount == heap->currentCount) {
		printf("赛 侩樊 弥措\n");
		return;
	}
	else {
		heap->currentCount++;
		int i = heap->currentCount;
		heap->pData[i] = node;
		while (0 < i) {
			if (heap->pData[i].frequency > heap->pData[i / 2].frequency) {
				HeapNode temp = heap->pData[i];
				heap->pData[i] = heap->pData[i / 2];
				heap->pData[i / 2] = temp;
			}
			i /= 2;
		}
	}
}
HeapNode* deleteMinHeap(ArrayMinHeap* heap) {
	HeapNode* temp = NULL;
	temp = (HeapNode*)malloc(sizeof(HeapNode));
	if (heap->currentCount > 0) {
		int parentIdx = 1, childrenIdx = 2;
		temp = &(heap->pData[parentIdx]);
		while (childrenIdx < heap->currentCount) {
			if (heap->pData[childrenIdx].frequency < heap->pData[childrenIdx + 1].frequency) {
				childrenIdx++;
			}
			heap->pData[parentIdx] = heap->pData[childrenIdx];
			parentIdx = childrenIdx;
			childrenIdx = childrenIdx * 2;
		}
		heap->currentCount--;
	}
	return temp;
}

HuffmanTreeNode* makeNewHuffmanNode(char data) {
	HuffmanTreeNode* pReturn = NULL;
	pReturn = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
	if (pReturn != NULL) {
		pReturn->data = data;
		pReturn->left = NULL;
		pReturn->right = NULL;
	}
	return pReturn;
}
HuffmanTree* makeHuffmanTree(HuffmanTreeNode* rootNode) {
	HuffmanTree* pReturn = NULL;
	pReturn = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	if (pReturn != NULL) {
		pReturn->root = rootNode;
	}
	return pReturn;
}
HuffmanTree* buildHuffmanTree(ArrayMinHeap *heap) {
	HuffmanTree* pReturn = NULL;
	pReturn = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	if (pReturn != NULL) {
		while (heap->currentCount > 0) {
			HeapNode* left = deleteMinHeap(heap);
			HeapNode* right = deleteMinHeap(heap);
			if (left != NULL && right != NULL) {
				HeapNode heapNode = { 0, };
				HuffmanTreeNode *huffNode=NULL;
				huffNode = makeNewHuffmanNode("?");
				huffNode->left = left;
				huffNode->right = right;
				heapNode.frequency = left->frequency + right->frequency;
				heapNode.pData = huffNode;
				appendMinHeap(heap, heapNode);
				free(right);
				free(left);
			}
		}
	}
	HeapNode* lastNode = deleteMinHeap(heap);
	if (lastNode != NULL) {
		pReturn = makeHuffmanTree(lastNode);
	}
	return pReturn;
}

void _recursiveHuffmanTree(HuffmanTreeNode *node,HuffmanCode table[],char code[],int codeIdx){
	if (node->left == NULL && node->right == NULL) {
	}
	else {
		if (node->left) _recursiveHuffmanTree(node->left, table,code,codeIdx);
		if (node->right) _recursiveHuffmanTree(node->right, table,code,codeIdx);
	}
};
void applyHuffmanTree(HuffmanTree* tree, HuffmanCode table[]) {
	HuffmanTreeNode* node = tree->root;
	char code[100];
	_recursiveHuffmanTree(node,table,code,0);
};

HuffmanCodeTable* createTable(char str[]) {
	HuffmanCode* arr;
	HuffmanCodeTable* pReturn = (HuffmanCodeTable*)malloc(sizeof(HuffmanCodeTable));
	int i = 0, idx = 0;
	char* p;
	arr = (HuffmanCode*)malloc(sizeof(HuffmanCode) * COUNT_ASC);
	if (arr != NULL) {
		memset(arr,0,sizeof(HuffmanCode)*COUNT_ASC);
		for (p = str; *p; p++) {
			idx = *p + 0;
			arr[idx].data = *p;
			arr[idx].frequency++;
		}
	}
	ArrayMinHeap* heap = createArrayHeap(COUNT_ASC);
	for (i = 0; i < COUNT_ASC; i++) {
		if (arr[i].frequency>0) {
			HeapNode heapNode = { 0 };
			heapNode.frequency = arr[i].frequency;
			heapNode.pData = makeNewHuffmanNode(arr[i].data);
			appendMinHeap(heap, heapNode);
		}
	}
	HuffmanTree* huffmanTree = buildHuffmanTree(heap);
	applyHuffmanTree(huffmanTree,arr);
	if (pReturn != NULL) {
		pReturn->idx = arr;
	}
	free(heap);
	return pReturn;
}
int main() {
	char str[100] = "abcde";
	char* p;
	HuffmanCodeTable *table=createTable(str);

	return 0;
}