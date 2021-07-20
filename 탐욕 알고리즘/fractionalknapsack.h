#ifndef fractionalknapsack_h
#define fractionalknapsack_h

#include <stdio.h>
#include <stdlib.h>

typedef struct KnapsackItem {
	char name[100];
	double weight;
	double profit;
	double selected;
}KnapsackItem;

typedef struct KnapsackType {
	struct KnapsackItem* items;
	int item_count;
	double max_capacity;
}KnapsackBag;
void displaySortItems(KnapsackItem items[], int count);
void displaySortBag(KnapsackBag* bag);
void maxProfit(KnapsackBag* bag);
void changeCapacity(KnapsackBag* bag);
int getPivot(KnapsackItem items[], int start, int end);
void quickSortItems(KnapsackItem items[], int start, int end);
KnapsackItem* getItems(int count);
KnapsackBag* createBag();
#endif
