#ifndef _HASH_CHAIN_
#define _HASH_CHAIN_

#include "hashdef.h";
#include "lindedlist.h";

typedef struct HashTableType {
	int bucketSize;
	int currentCount;
	struct LinkedListType** ppBucket;
}HashTable;

HashTable* createHashTable(int bucketSize);
int addData(HashTable* pHashTable, HashSlot slot);
int removeData(HashTable* pHashTable, char* key);
HashSlot* search();
void displayHashTable(HashTable* pHashTable);
int getCount(HashTable* pHashTable);
void deleteHashTable(HashTable* pHashTable);

//내부 함수
LinkedList* searchBucket(HashTable* pHashTable, char* key);
int addLinkedListDataLast(LinkedList *pBucket,HashSlot data);
int hashFunction(char *pKey,int bucketSize);
unsigned int stringToInt(char* pKey);
HashSlot* searchSlot(LinkedList *pList,char*key,int* pPosition);
#endif
