#ifndef _ZERO_ONE_KNAPSACK_
#define _ZERO_ONE_KNAPSACK_

#include <stdio.h>
#include <stdlib.h>

typedef struct KnapsackItem {
	char name[100];
	int weight;
	int profit;
	int selected;
}KnapsackItem;

typedef struct KnapsackType {
	struct KnapsackItem* items;
	int item_count;
	int max_capacity;
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
