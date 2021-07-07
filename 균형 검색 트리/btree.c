#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

BTree* createBTree() {
	BTree* pReturn = NULL;
	pReturn = (BTree*)malloc(sizeof(BTree));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree));
	}
	return pReturn;
};
void deleteBTree(BTree* pBTree) {};

BTreeNodeData* searchBT(BTree* pBtree, int key) {
	BTreeNodeData* pReturn = NULL;
	BTreeNode* pCurrentNode = NULL;
	int i = 0;
	if (pBtree != NULL) {
		pCurrentNode = pBtree->pRootNode;
		while (pCurrentNode != NULL) {
			for (i = 0; i < pCurrentNode->count; i++) {
				int currentKey = pCurrentNode->data[i].key;
				if (currentKey == key) {
					pReturn = &(pCurrentNode->data[i]);
					return pReturn;
				}
				else if (key < currentKey) {
					break;
				}
			}
			pCurrentNode = pCurrentNode->children[i];
		}
	}
	return pReturn;
}
int addDataBT(BTree* pBTree, BTreeNodeData data) {
	int ret = 1;
	int i = 0;
	BTreeNode* pParentNode = NULL, *pCurrentNode = NULL;
	LinkedStack* pStack = NULL;
	pStack = createLinkedStack();

	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL) {
		pushLS(pStack, pCurrentNode);
		pParentNode = pCurrentNode;
		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (data.key == currentKey) {
				printf("오류, 중복된 키 \n");
				ret = 0;
				deleteLinkedStack(pStack);
				return ret;
			}
			else if (data.key < currentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->children[i];
	}
	if (pParentNode == NULL) {
		pBTree->pRootNode = createBTreeNode(data);
	}
	else {
		addNodeBT(pParentNode,data,NULL);
		splitNodeBT(pBTree,pStack);
	}
	ret = 1;
	deleteLinkedStack(pStack);
	return ret;
}
int removeDataBT(BTree* pBTree, int key) {
	int ret = 1;
	int i = 0;
	int isFind = 0;
	BTreeNode* parentNode = NULL;
	BTreeNode* currentNode = NULL;
	LinkedStack* pStack = NULL;
	pStack = createLinkedStack();
	currentNode = pBTree->pRootNode;
	while (currentNode!=NULL&&isFind==0) {
		parentNode = currentNode;
		pushLS(pStack,parentNode);
		for (i = 0; i < currentNode->count; i++) {
			int currentKey = currentNode->data[i].key;
			if (key == currentKey) {
				isFind = 1;
				break;
			}
			else if (key < currentKey) {
				break;
			}
		}
		currentNode = currentNode->children[i];
	}
	if (isFind == 1) {
		if (isLeafNode(parentNode) == 0) {
			parentNode = replaceLeafNodeBT(pBTree,parentNode,i,pStack);
		}
		else {
			deleteKeyBT(parentNode, i);
		}
		if (parentNode->count<(BTREE_ORDER/2)) {
			balanceBTree(pBTree, pStack);
		}
		ret = 1;
	}else {
		ret = 0;
		printf("오류, 검색키가 발견되지 않음\n");
	}
	deleteLinkedStack(pStack);
	return ret;
}
void displayBTree(BTree* pBTree) {
	if (pBTree != NULL) {
		displayBTreeNode(pBTree->pRootNode,0);
	}
}

//내부 함수
BTreeNode* createBTreeNode(BTreeNodeData data){
	BTreeNode* pReturn = NULL;            
	pReturn = (BTreeNode*)malloc(sizeof(BTreeNode));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTreeNode));
		pReturn->data[0] = data;
		pReturn->count=1;
	}
	return pReturn;
}
void addNodeBT(BTreeNode *currentNode,BTreeNodeData data,BTreeNode *rightChildNode){
	int i = 0,pre=0;
	if (currentNode->count == BTREE_ORDER) return;
	for (i = 0; i < currentNode->count; i++) {
		if (data.key < currentNode->data[i].key) {
			pre = i;
			break;
		}
		else if (i == currentNode->count) {
			pre = i;
			break;
		}
	}
	for (i = currentNode->count-1; pre<=i ; i--) {
		currentNode->data[i+1]= currentNode->data[i];
		currentNode->children[i + 2] = currentNode->children[i + 1];
	}
	currentNode->data[pre] = data;
	currentNode->children[pre + 1] = rightChildNode;
	currentNode->count++;
}
void splitNodeBT(BTree *Btree, LinkedStack*stack){
	LinkedStackNode* parentStackNode = NULL;
	LinkedStackNode* currentStackNode = NULL;
	BTreeNode* currentTreeNode=NULL;
	BTreeNode* newTreeNode = NULL;
	BTreeNodeData pivotElement = {0,};
	int pivotIndex = BTREE_ORDER / 2;
	int i = 0;

	if (stack == NULL) return;
	currentStackNode = popLS(stack);
	while (currentStackNode != NULL) {
		currentTreeNode = currentStackNode->data;
		if (currentTreeNode->count >= BTREE_ORDER) {
			newTreeNode = (BTreeNode*)malloc(sizeof(BTreeNode));
			if (newTreeNode != NULL) {
				memset(newTreeNode, 0, sizeof(BTreeNode));
			}
			else {
				printf("새로운 노드 선언이 안됨!!");
				break;
			}
			pivotElement= currentTreeNode->data[pivotIndex];
			memset(&currentTreeNode->data[pivotIndex], 0, sizeof(BTreeNodeData));

			for (i = pivotIndex + 1; i < BTREE_ORDER; i++) {
				newTreeNode->data[i - pivotIndex - 1] = currentTreeNode->data[i];
				newTreeNode->children[i - pivotIndex - 1] = currentTreeNode->children[i];

				memset(&currentTreeNode->data[i], 0, sizeof(BTreeNodeData));
				currentTreeNode->children[i] = NULL;
			}
			newTreeNode->children[i - pivotIndex - 1] = currentTreeNode->children[i];
			currentTreeNode->children[i] = NULL;
			newTreeNode->count = BTREE_ORDER - pivotIndex - 1;
			currentTreeNode->count = pivotIndex;

			parentStackNode = popLS(stack);
			if (parentStackNode != NULL) {
				addNodeBT(parentStackNode->data, pivotElement, newTreeNode);
			}
			else {
				Btree->pRootNode = createBTreeNode(pivotElement);
				Btree->pRootNode->children[0] = currentTreeNode;
				Btree->pRootNode->children[1] = newTreeNode;
			}
		}
		if (currentStackNode != NULL) {
			free(currentStackNode);
		}
		currentStackNode = parentStackNode;
		parentStackNode = NULL;
	}

	if (currentStackNode != NULL) free(currentStackNode);
	if (parentStackNode != NULL) free(parentStackNode);
}

void displayBTreeNode(BTreeNode *Node,int floor){
	int i;
	if (Node != NULL) {
		printf("높이: %d", floor);
		for (i = 0; i < Node->count; i++) {
			printf("(%d,%c) ", Node->data[i].key, Node->data[i].value);
		}
		printf("\n");
		for (i = 0; i < Node->count + 1; i++) {
			displayBTreeNode(Node->children[i],floor+1);
		}
	}
}

int isLeafNode(BTreeNode* parentNode) {
	int ret = 0;
	if (parentNode != NULL) {
		if (parentNode->children[0] == NULL) {
			ret = 1;
		}
	}
	return ret;
}
void balanceBTree(BTree* tree,LinkedStack *stack) {
	LinkedStackNode* parentStackNode = NULL;
	LinkedStackNode* currentStackNode = NULL;
	BTreeNode* currentTreeNode = NULL;
	BTreeNode* parentTreeNode = NULL;
	int index;
	currentStackNode = popLS(stack);
	if (currentStackNode == NULL) {
		return;
	}
	currentTreeNode = currentStackNode->data;
	if (currentTreeNode->count >= BTREE_ORDER / 2) {
		free(currentStackNode);
		return;
	}
	parentStackNode = popLS(stack);
	if (parentStackNode == NULL) {
		free(currentStackNode);
		return;
	}
	parentTreeNode = parentStackNode->data;
	index = getCurrentIndex(parentTreeNode,currentTreeNode);
	if (index < parentTreeNode->count && parentTreeNode->children[index + 1]->count >= (BTREE_ORDER / 2 + 1)) {
		borrowRight(parentTreeNode,index,currentTreeNode,parentTreeNode->children[index+1]);
	}else if(index>0 &&parentTreeNode->children[index-1]->count>=(BTREE_ORDER/2+1)){
		borrowLeft(parentTreeNode,index,currentTreeNode,parentTreeNode->children[index-1]);
	}
	else {
		mergeNode(tree, stack,parentTreeNode,currentTreeNode,index);
	}
}

int getCurrentIndex(BTreeNode* parent, BTreeNode* current) {
	int i = 0,ret=0;
	for (i = 0; i < parent->count; i++) {
		if (parent->children[i] == current) {
			ret = i;
			break;
		}
	}
	return ret;
}
void borrowRight(BTreeNode *parent,int index,BTreeNode *current,BTreeNode *right) {
	current->data[current->count] = parent->data[index];
	current->count++;
	parent->data[index] = right->data[0];
	deleteKeyBT(right,0);
}
void borrowLeft(BTreeNode* parent, int index, BTreeNode* current, BTreeNode* left) {
	BTreeNodeData leftElement= { 0, };
	BTreeNodeData parentElement = { 0, };

	int count=left->count;
	leftElement = left->data[count];
	parentElement = parent->data[index-1];
	deleteKeyBT(left,count-1);
	parent->data[index-1] = leftElement;
	addNodeBT(current, parentElement,NULL);
}
void mergeNode(BTree *tree,LinkedStack *stack,BTreeNode*parent,BTreeNode*current,int index){
	LinkedStackNode* parentStackNode = NULL;
	BTreeNode* parentParentNode = NULL;
	BTreeNode* leftNode = NULL;
	BTreeNode* rightNode = NULL;
	BTreeNodeData parentElement = { 0, };
	int pivotIndex = 0;
	int i = 0;
	if(index<parent->count){
		leftNode = current;
		rightNode = parent->children[index+1];
		pivotIndex = index;
		parentElement = parent->data[pivotIndex];
	}
	else {
		leftNode = parent->children[index - 1];
		rightNode = current;
		pivotIndex = index - 1;
		parentElement = parent->data[pivotIndex];
	}
	addNodeBT(leftNode,parentElement,rightNode->children[0]);
	for (i = 0; i < rightNode->count; i++) {
		addNodeBT(leftNode, rightNode->data[i], rightNode->children[i + 1]);
	}
	deleteKeyBT(parent,pivotIndex);
	free(rightNode);
	//내부 노드의 서브트리 개수
	if (parent->count==0) {
		free(tree->pRootNode);
		tree->pRootNode = leftNode;
	}
	else if (parent->count < (BTREE_ORDER / 2)) {
		int index = 0;
		parentStackNode = popLS(stack);
		if (parentStackNode != NULL) {
			parentParentNode = parentStackNode->data;
			index = getCurrentIndex(parentParentNode,parent);
			mergeNode(tree,stack,parentParentNode,parent,index);
			free(parentStackNode);
		}
	}
}

BTreeNode *replaceLeafNodeBT(BTree *pBTree,BTreeNode* delNode,int index,LinkedStack* pStack){
	BTreeNode* pReturn = NULL;
	BTreeNodeData leafNodeElement = { 0, };
	BTreeNode* ChildNode = NULL;
	BTreeNode* ParentNode = delNode;
	int count = index;
	if (pBTree == NULL || delNode == NULL) return pReturn;

	do {
		ChildNode = ParentNode->children[count];
		pushLS(pStack, ChildNode);
		count = ChildNode->count;
		ParentNode = ChildNode;
	} while (ChildNode->children[count] != NULL);

	leafNodeElement = ChildNode->data[count - 1];
	delNode->data[index] = leafNodeElement;
	deleteKeyBT(ChildNode, count - 1);
	pReturn = ChildNode;
	return pReturn;
}

void deleteKeyBT(BTreeNode* Node,int index){
	int i = 0;
	if (Node != NULL) {
		for (i = index + 1; i < Node->count; i++) {
			Node->data[i - 1] = Node->data[i];
			Node->children[i] = Node->children[i + 1];
		}
		memset(&Node->data[Node->count-1],0,sizeof(BTreeNodeData));
		Node->children[Node->count] = NULL;

		Node->count--;
	}
}