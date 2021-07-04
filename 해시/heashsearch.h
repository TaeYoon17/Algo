#ifndef _HASH_SEARCH_
#define _HASH_SEARCH_

#define HASH_KEY_SIZE 30

typedef enum HashBucketStatusType {EMPTY=0,USED,DELETED} HashBucketStatus;

typedef struct HashBucketType {
	char key[HASH_KEY_SIZE + 1];
	int value;
	HashBucketStatus status;
}HashBucket;

typedef struct HashTableType {
	int bucketSize;
	int currentCount;
	HashBucket* pBucket;
} HashTable;

//CRUD -> DATA AND HASHTABLE
HashTable* createdHashTable(int bucketSize);
int addData(HashTable* pHashTable, HashBucket bucket);
int removeData(HashTable* pHashTable, char* key);
HashBucket* search(HashTable* pHashTable, char* key);
void displayHashTable(HashTable* pHashTable);
int getCount(HashTable* pHashTable);
void deleteHashTable(HashTable* pHashTable);
//내부 사용 함수
int hashFunction(char* pKey, int bucketSize);
unsigned int stringToInt(char* pKey);
//int isEmptyBucket(HashBucket* pBucket);
int isEmptyOrDeletedBucket(HashBucket* pBucket);

#endif
