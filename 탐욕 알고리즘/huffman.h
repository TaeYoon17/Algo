#ifndef _HUFFMAN_
#define _HUFFMAN_
#define MAX_BIT_SIZE 8
#define COUNT_ASC 128
#include "arrayheap.h"
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
HuffmanTreeNode* makeNewHuffmanNode(char data);
HuffmanTree* makeHuffmanTree(HuffmanTreeNode* rootNode);
HuffmanTree* buildHuffmanTree(ArrayMinHeap* minHeap);
void _recursiveHuffmanTree(HuffmanTreeNode* node, HuffmanCode table[], char code[]);
void applyHuffmanTree(HuffmanTree* tree, HuffmanCode table[]);
void displayHuffmanCodeArray(HuffmanCode* arr);
HuffmanCodeTable* createTable(char str[]);
#endif