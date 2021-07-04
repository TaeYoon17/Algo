#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heashsearch.h"

HashTable* createdHashTable(int bucketSize) {
	if (bucketSize <= 0) {
		printf("��Ŷ�� 0���� Ŀ����");
		return NULL;
	}
	HashTable *pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->bucketSize = bucketSize;
		pReturn->currentCount = 0;
		pReturn->pBucket = NULL;
	}
	else {
		printf("����, ù��° �޸��Ҵ�, createdHashTable()\n");
		return NULL;
	}
	pReturn->pBucket = (HashBucket*)malloc(sizeof(HashBucket) * bucketSize);
	if (pReturn->pBucket != NULL)
		memset(pReturn->pBucket, 0, sizeof(HashBucket) * bucketSize); // �޸� �ʱ�ȭ
	else {
		if (pReturn != NULL) free(pReturn);
		printf("����, �ι�° �޸��Ҵ�,createdHashTable()\n");
		return NULL;
	}
	return pReturn;
}
int addData(HashTable* pHashTable, HashBucket bucket) {
	int ret = 0;
	HashBucket* pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;
	int inc = 1;
	if (pHashTable == NULL) {
		printf("NULL-�ؽ����̺�");
		ret = 0;
		return ret;
	}
	bucketIndex = hashFunction(bucket.key, pHashTable->bucketSize);
	if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
		printf("�߸��� �ؽ� ���̺� �ּ� ���");
		return ret;
	}
	tempIndex = bucketIndex;
	do {
		pBucket = &(pHashTable->pBucket[tempIndex]);
		if (isEmptyOrDeletedBucket(pBucket) == 1) {
			pHashTable->pBucket[tempIndex] = bucket;
			pHashTable->pBucket[tempIndex].status = USED;
			pHashTable->currentCount++;
			ret = 1;
			break;
		}
		else {
			if (strcmp(pBucket->key, bucket.key) == 0) {
				printf("�ߺ��� Ű %s", bucket.key);
				ret = 0;
				break;
			}
			else {
				tempIndex = (tempIndex + inc) % pHashTable->bucketSize;

				if (tempIndex == bucketIndex) {
					printf("������ �ؽ� ���̺�\n");
					ret = 0;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex);
	return ret;
}
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashBucket* pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;

	if (pHashTable == NULL) {
		printf("NULL-�ؽ� ���̺��Դϴ�.\n");
		return ret;
	}
	else {
		pBucket = search(pHashTable, key);
		if (pBucket != NULL) {
			pBucket->status = DELETED;
			pBucket->key[0] = '\0';
			pBucket->value = 0;
			pHashTable->currentCount--;
			ret = 1;
		}
		else {
			printf("���� ����, �˻�Ű�� �������� ����");
		}
	}
	return ret;
}
HashBucket* search(HashTable* pHashTable, char* key) {
	HashBucket* pReturn = NULL;
	HashBucket* pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;

	if (pHashTable == NULL) {
		printf("NULL-�ؽ� ���̺��Դϴ�.\n");
		pReturn = NULL;
		return pReturn;
	}
	bucketIndex = hashFunction(key, pHashTable->bucketSize);
	if (bucketIndex < 0) {
		printf("�߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�.\n");
		pReturn = NULL;
		return pReturn;
	}
	tempIndex = bucketIndex;
	do{
		pBucket = &(pHashTable->pBucket[tempIndex]);
		if (isEmptyOrDeletedBucket(pBucket) == 1) {
			printf("�˻� ����, �˻�Ű�� �������� �ʽ��ϴ�.");
			pReturn = NULL;
			break;
		}
		else {
			if (pBucket->status == USED &&
				strcmp(pBucket->key, key) == 0) {
				pReturn = pBucket;
				break;
			}
			else {
				tempIndex = (tempIndex + 1) % pHashTable->bucketSize;

				if (tempIndex == bucketIndex) {
					printf("�˻�Ű�� �������� �ʽ��ϴ�.");
					pReturn = NULL;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex);
	return pReturn;
}
void displayHashTable(HashTable* pHashTable){
	int i = 0;
	int bucketIndex = 0;
	HashBucket* pBucket = NULL;
	if (pHashTable != NULL) {
		printf("-------------------------\n");

		for (i = 0; i < pHashTable->bucketSize; i++) {
			printf("[%d]", i);

			pBucket = &(pHashTable->pBucket[i]);
			if (pBucket->key[0] != '\0') {
				bucketIndex = hashFunction(pBucket->key, pHashTable->bucketSize);
				printf("%s, (%d->%d),[%d]\n", pBucket->key, bucketIndex, i, pBucket->value);
			}
			else {
				printf("������ϴ�.\n");
			}
		}
		printf("-------------------------------------\n");
	}
	else {
		printf("NULL �ؽ� ���̺��Դϴ�.");
	}
}
int getCount(HashTable* pHashTable){
	int ret = 0;
	if (pHashTable != NULL) {
		ret= pHashTable->currentCount;
	}
	return ret;
}
void deleteHashTable(HashTable* pHashTable){
	if (pHashTable != NULL) {
		free(pHashTable->pBucket);
	}
	free(pHashTable);
}

//���� ��� �Լ�
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
int isEmptyOrDeletedBucket(HashBucket* pBucket) {
	int ret = 0;
	if (pBucket != NULL) {
		if (pBucket->status == EMPTY || pBucket->status == DELETED) {
			ret = 1;
		}
	}
	return ret;
}
