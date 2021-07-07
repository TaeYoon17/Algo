#ifndef _B_TREE_
#define _B_TREE_
#include "btreedef.h";
#include "blinkedstack.h";

typedef struct BTreeType {
	BTreeNode* pRootNode;
}BTree;

BTree* createBTree();
void deleteBTree(BTree* pBTree);

BTreeNodeData* searchBT(BTree *pBtree,int key);
int addDataBT(BTree*pBTree, BTreeNodeData data);
int removeDataBT(BTree *pBTree,int key);
void displayBTree(BTree*pBTree);
//내부 함수
BTreeNode* createBTreeNode(BTreeNodeData data);
void addNodeBT(BTreeNode* currentNode, BTreeNodeData data, BTreeNode* rightChildNode);
void splitNodeBT(BTree* Btree, LinkedStack* stack);
void displayBTreeNode(BTreeNode* Node);
#endif