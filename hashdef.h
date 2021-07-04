#ifndef _HASH_DEF_
#define _HASH_DEF_

#define MASH_KEY_SIZE 10
typedef struct HashSlotType {
	char key[MASH_KEY_SIZE + 1];
	int value;
}HashSlot;
#endif