#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "zerooneKnapsack.h"

void displaySortItems(KnapsackItem items[], int count) {
	int i = 0;
	printf("\t이름\t무게\t가치\t비율\n");
	for (i = 0; i < count; i++) {
		printf("%d\t%s\t%d\t%d\t%.2f\n", i, items[i].name, items[i].weight, items[i].profit, (items[i].profit / items[i].weight)+0.0);
	}
	return;
}
void displaySortBag(KnapsackBag* bag) {
	displaySortItems(bag->items, bag->item_count);
	return;
}
KnapsackBag* ShallowCopyBag(KnapsackBag* bag) {
	KnapsackBag* newBag = (KnapsackBag*)malloc(sizeof(KnapsackBag));
	KnapsackItem* newItem =NULL;
	if (newBag != NULL) {
		newBag->item_count = bag->item_count;
		newBag->max_capacity = bag->max_capacity;
		newItem = (KnapsackItem*)malloc(sizeof(KnapsackItem));
		printf("item_count %d\n",newBag->item_count);
		if (newItem != NULL) {
			printf("hello\n");
			for (int i = 0; i < newBag->item_count; i++) {
				newItem[i] = bag->items[i];
				printf("i: %d\n", i);
			}
		}
		else {
			printf("isError!!");
			return NULL;
		}
		newBag->items = newItem;
	}
	else {
		printf("error!!");
		return NULL;
	}
	return newBag;
}
void _maxProfit(KnapsackBag* bag, int capacity) {
	int i = 0;
	int count = bag->item_count;
	if (capacity <= 0) {
		displaySortBag(bag);
		return;
	}
	else {
	for (i = 0; i < count; i++) {
		KnapsackBag* newBag = ShallowCopyBag(bag);
		if (newBag->items[i].selected == 0&&newBag->items[i].weight<=capacity) {
			newBag->items[i].selected = 1;
			return _maxProfit(newBag, capacity - newBag->items[i].weight);
		}
	}
	free(bag);
	}
}
void maxProfit(KnapsackBag* bag) {
	int nowCapacity = bag->max_capacity;
	KnapsackBag* newBag = ShallowCopyBag(bag);
	displaySortBag(newBag);
	//_maxProfit(newBag, nowCapacity);
	return;
}

void changeCapacity(KnapsackBag* bag) {
	double n;
	printf("가방 용량을 입력하세요:");
	scanf("%lf", &n);
	if (bag != NULL)bag->max_capacity = n;
	maxProfit(bag);
}

int getPivot(KnapsackItem items[], int start, int end) {
	int pivot = end;
	int right = end;
	int left = start;
	double leftRatio = 0, rightRatio = 0, pivotRatio = 0;
	KnapsackItem temp = { 0 };
	while (left < right) {
		leftRatio = items[left].profit / items[left].weight;
		rightRatio = items[right].profit / items[right].weight;
		pivotRatio = items[pivot].profit / items[pivot].weight;
		while ((leftRatio > pivotRatio) && (left < right)) {
			left++;
			leftRatio = items[left].profit / items[left].weight;
		}
		while ((rightRatio <= pivotRatio) && (left < right)) {
			right--;
			rightRatio = items[right].profit / items[right].weight;
		}
		if (left < right) {
			temp = items[left];
			items[left] = items[right];
			items[right] = temp;
		}
	}
	temp = items[pivot];
	items[pivot] = items[right];
	items[right] = temp;

	return right;
}

void quickSortItems(KnapsackItem items[], int start, int end) {
	int pivot = 0;
	if (start < end) {
		pivot = getPivot(items, start, end);
		quickSortItems(items, start, pivot - 1);
		quickSortItems(items, pivot + 1, end);
	}
}

KnapsackItem* getItems(int count) {
	KnapsackItem* pReturn = NULL;
	int i = 0;
	pReturn = (KnapsackItem*)malloc(sizeof(KnapsackItem));
	if (pReturn != NULL) {
		for (i = 0; i < count; i++) {
			int weight, profit;
			printf("%d번째 물건의 이름:", i + 1);
			scanf("%s", pReturn[i].name);
			getchar();
			printf("물건의 무게와 금액: ");
			scanf("%d %d", &weight, &profit);
			getchar();
			if (profit < 0 || weight < 0) {
				printf("음수는 안됩니다.");
				i--;
			}
			else {
				pReturn[i].selected = 0;
				pReturn[i].profit = profit;
				pReturn[i].weight = weight;
			}
		}
		quickSortItems(pReturn, 0, count - 1);
	}
	return pReturn;
}
KnapsackBag* createBag() {
	int count = 0;
	int n = 0;
	KnapsackBag* pReturn = NULL;
	pReturn = (KnapsackBag*)malloc(sizeof(KnapsackBag));
	printf("가방 전체 용량을 입력하세요: ");
	scanf("%d", &n);
	printf("물건 개수를 입력하세요: ");
	scanf("%d", &count);
	if (pReturn != NULL) {
		pReturn->max_capacity = n;
		pReturn->item_count = count;
		KnapsackItem* items = getItems(count);
		if (items != NULL) pReturn->items = items;
	}
	return pReturn;
}