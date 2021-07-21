#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


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
HuffmanTree* buildHuffmanTree(ArrayMinHeap* minHeap) {
	HuffmanTree* pReturn = NULL;
	pReturn = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	if (pReturn != NULL) {
		while (minHeap->currentCount > 1) {
			HeapNode* left = deleteMinHeap(minHeap);
			HeapNode* right = deleteMinHeap(minHeap);
			if (left != NULL && right != NULL) {
				HuffmanTreeNode* HuffLeft = left->pData, * HuffRight = right->pData;
				HeapNode heapNode = { 0, };
				HuffmanTreeNode* huffNode = NULL;
				huffNode = makeNewHuffmanNode("?");
				huffNode->left = HuffLeft;
				huffNode->right = HuffRight;
				heapNode.frequency = left->frequency + right->frequency;
				heapNode.pData = huffNode;
				appendMinHeap(minHeap, heapNode);
				free(right);
				free(left);
			}
		}
	}
	HeapNode* lastNode = deleteMinHeap(minHeap);
	if (lastNode != NULL) {
		pReturn = makeHuffmanTree(lastNode->pData);
	}
	return pReturn;
}

void _recursiveHuffmanTree(HuffmanTreeNode* node, HuffmanCode table[], char code[]) {
	char leftCode[2] = "0";
	char rightCode[2] = "1";
	if (node->left == NULL && node->right == NULL) {
		int index = (int)node->data;
		strcpy(table[index].bitString, code);
		strcpy(node->bitString, code);
	}
	else {
		if (node->left) {
			char newCode[100] = "";
			strcat(newCode, code);
			strcat(newCode, "0");
			_recursiveHuffmanTree(node->left, table, newCode);
		}
		if (node->right) {
			char newCode[100] = "";
			strcat(newCode, code);
			strcat(newCode, "1");
			_recursiveHuffmanTree(node->right, table, newCode);
		}
	}
};
void applyHuffmanTree(HuffmanTree* tree, HuffmanCode table[]) {
	HuffmanTreeNode* node = tree->root;
	if (node->left) {
		char code[100] = "0";
		_recursiveHuffmanTree(node->left, table, code);
	}
	if (node->right) {
		char code[100] = "1";
		_recursiveHuffmanTree(node->right, table, code);
	}
};

void displayHuffmanCodeArray(HuffmanCode* arr) {
	int i = 0;
	for (i = 0; i < COUNT_ASC; i++) {
		printf("idx: %d data: %c frenquency: %d bitString %s\n", i + 1, arr[i].data, arr[i].frequency, arr[i].bitString);
	}
}

HuffmanCodeTable* createTable(char str[]) {
	HuffmanCode* arr;
	HuffmanCodeTable* pReturn = (HuffmanCodeTable*)malloc(sizeof(HuffmanCodeTable));
	int i = 0, idx = 0;
	char* p;
	arr = (HuffmanCode*)malloc(sizeof(HuffmanCode) * COUNT_ASC);
	if (arr != NULL) {
		memset(arr, 0, sizeof(HuffmanCode) * COUNT_ASC);
		for (p = str; *p; p++) {
			idx = *p + 0;
			arr[idx].data = *p;
			arr[idx].frequency++;
		}
	}
	ArrayMinHeap* minHeap = createArrayHeap(COUNT_ASC);
	for (i = 0; i < COUNT_ASC; i++) {
		if (arr[i].frequency > 0) {
			HeapNode heapNode = { 0 };
			heapNode.frequency = arr[i].frequency;
			heapNode.pData = makeNewHuffmanNode(arr[i].data);
			appendMinHeap(minHeap, heapNode);
		}
	}
	HuffmanTree* huffmanTree = buildHuffmanTree(minHeap);
	if (huffmanTree == NULL) printf("매우 큰 오류!!");
	applyHuffmanTree(huffmanTree, arr);
	displayHuffmanCodeArray(arr);
	if (pReturn != NULL) {
		pReturn->idx = arr;
	}
	//	free(heap);
	return pReturn;
}