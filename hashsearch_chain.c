/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashsearch_chain.h";

HashTable* createHashTable(int bucketSize) {
	HashTable* pReturn = NULL;
	int i = 0;
	if (bucketSize <= 0) {
		printf("버킷 사이즈<=0\n");
		return NULL;
	}
	pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->bucketSize = bucketSize;
		pReturn->currentCount = 0;
		pReturn->ppBucket = NULL;
	}
	else {
		printf("해시 테이블 할당 오류\n");
		return NULL;
	}

	pReturn->ppBucket = (LinkedList**)malloc(sizeof(LinkedList*) * bucketSize);
	if (pReturn->ppBucket != NULL) {
		memset(pReturn->ppBucket, 0, sizeof(LinkedList*) * bucketSize);
		for (i = 0; i < bucketSize; i++) {
			pReturn->ppBucket[i] = createLinkedList();
		}
	}
	else {
		printf("버킷 리스트 할당 오류\n");
		return NULL;
	}
	return pReturn;
};
int addData(HashTable* pHashTable, HashSlot slot) {
	int ret = 0;
	LinkedList* pBucket = NULL;
	if (pHashTable != NULL) {
		pBucket = searchBucket(pHashTable, slot.key);
		if (pBucket != NULL) {
			ret=addLinkedListDataLast(pBucket, slot);
			pHashTable->currentCount++;
		}
	}
	else {
		printf("해시 테이블 주소 오류\n");
		ret = 0;
	}

	return ret;
};
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	LinkedList* pBucket = NULL;
	HashSlot* pHashSlot = NULL;
	int position = 0;
	if (pHashTable != NULL) {
		pBucket = searchBucket(pHashTable, key);
		if (pBucket != NULL) {
			pHashSlot = searchSlot(pBucket, key, &position);
			if (pHashSlot != NULL) {
				ret = removeLinkedListData(pBucket, position);
				pHashTable->currentCount--;
			}
		}
	}
	else {
		printf("해시 테이블 주소 오류\n");
		ret = 0;
	}
	return ret;
}
HashSlot* search();
void displayHashTable(HashTable* pHashTable) {
	int i = 0, j = 0;
	int slotSize = 0;
	LinkedList* pList = NULL;
	LinkedListNode* pNode = NULL;
	if (pHashTable != NULL) {
		for (i = 0; i < pHashTable->bucketSize; i++) {
			printf("[%d]", i);

			pList = pHashTable->ppBucket[i];
			slotSize = getLinkedListLength(pList);
			if (slotSize == 0) {
				printf(",Empty \n");
			}
			else {
				pNode = pList->headerNode.pLink;
				for (j = 0; j < slotSize; j++) {
					printf(",(%s, %d)", pNode->data.key, pNode->data.value);
					pNode = pNode->pLink;
				}
				printf("\n");
			}
		}
	}
	else {
		printf("해시 테이블 없음");
	}
}
int getCount(HashTable* pHashTable) {

}
void deleteHashTable(HashTable* pHashTable) {
	int i = 0;
	LinkedList* pLinkedList;
	if (pHashTable != NULL) {
		if (pHashTable->ppBucket != NULL) {
			for (i = 0; i < pHashTable->bucketSize; i++) {
				deleteLinkedList(pHashTable->ppBucket[i]);
			}
			free(pHashTable->ppBucket);
		}
		free(pHashTable);
	}
}

LinkedList* searchBucket(HashTable* pHashTable, char* key) {
	LinkedList* pReturn = NULL;
	int bucketIndex = 0;
	if (pHashTable != NULL) {
		bucketIndex = hashFunction(key, pHashTable->bucketSize);
		if (bucketIndex >= 0) {
			pReturn = pHashTable->ppBucket[bucketIndex];
		}
		else {
			printf("해시 함수 오류");
		}
	}
	return pReturn;
};
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data) {
	int ret = 0;
	if (pBucket != NULL) {
		int position = pBucket->currentCount;
		ret = addLinkedListData(pBucket, position, data);
	}
	return ret;
}
int hashFunction(char* pKey, int bucketSize) {
	int ret = -1;
	unsigned int temp_key = 0;
	if (pKey == NULL) {
		return ret;
	}
	temp_key = stringToInt(pKey);
	if (bucketSize > 0) {
		ret = temp_key % bucketSize;
	}
	return ret;
}
unsigned int stringToInt(char* pKey) {
	unsigned int ret = 0;
	while (*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		pKey++;
	}
	return ret;
}
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition) {
	HashSlot *pReturn = NULL;
	LinkedListNode* pSlot = NULL;
	int index = 0;
	if (pList != NULL &&pPosition!=NULL) {
		pSlot = pList->headerNode.pLink;
		while (pSlot != NULL) {
			if (strcmp(pSlot->data.key, key) == 0) {
				pReturn = &(pSlot->data);
				*pPosition = index;
				break;
			}
			index++;
			pSlot = pSlot->pLink;
		}
		if (pReturn == NULL) {
			printf("해당 검색키는 존재하지 않습니다.");
		}
	}
	return pReturn;
}*/