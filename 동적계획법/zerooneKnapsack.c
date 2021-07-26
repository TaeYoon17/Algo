#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "zerooneKnapsack.h"

void displaySortItems(KnapsackItem items[], int count) {
	int i = 0;
	printf("\t이름\t무게\t가치\t비율\n");
	for (i = 0; i < count; i++) {
		float ratio = (items[i].profit*1.0) / (items[i].weight*1.0);
		printf("%d\t%s\t%d\t%d\t%.2f\n", i, items[i].name, items[i].weight, items[i].profit, ratio);
	}
	return;
}
void displaySortBag(KnapsackBag* bag) {
	displaySortItems(bag->items, bag->item_count);
	return;
}
void freeBag(KnapsackBag* bag) {
	if (bag != NULL) {
		free(bag);
		if (bag->items != NULL)free(bag->items);
	}
}
KnapsackBag* ShallowCopyBag(KnapsackBag* bag) {
	KnapsackBag* newBag = (KnapsackBag*)malloc(sizeof(KnapsackBag));
	KnapsackItem* newItems =NULL;
	if (newBag != NULL) {
		newBag->item_count = bag->item_count;
		newBag->max_capacity = bag->max_capacity;
		newBag->now_capacity = bag->now_capacity;
		newItems = (KnapsackItem*)malloc(sizeof(KnapsackItem)*(newBag->item_count));
		if (newItems != NULL) {
			for (int i = 0; i < newBag->item_count; i++) newItems[i] = bag->items[i];
		}
		else {
			printf("isError!!");
			return NULL;
		}
		newBag->items = newItems;
	}
	else {
		printf("error!!");
		return NULL;
	}
	return newBag;
}
void displaySelectedItem(KnapsackBag* bag) {
	int count=bag->item_count,i=0;
	for (i = 0; i < count; i++) {
		if (bag->items[i].selected == 1) {
			printf("name: %s profit: %d, weight: %d\n", bag->items[i].name, bag->items[i].profit, bag->items[i].weight);
		}
	}
	printf("\n");
}
KnapsackBag* _maxProfit(KnapsackBag* bag,int start) {
	int i = 0,nowCapa=bag->now_capacity;
	int count = bag->item_count;
	KnapsackBag* nowBag=bag;
	if (nowCapa == 0) {
		return NULL;
	}
	else if (nowCapa < 0) {
		printf("잘 못 됨");
		return NULL;
	}
	else {
		for (i = start; i < count; i++) {
			KnapsackBag* newBag = ShallowCopyBag(bag);
			if (newBag->items[i].selected == 0&&newBag->items[i].weight<=newBag->now_capacity) {
				newBag->items[i].selected = 1;
				newBag->now_capacity -= newBag->items[i].weight;
				KnapsackBag* tempBag=_maxProfit(newBag, i);
				if (tempBag->now_capacity < nowCapa&&tempBag!=NULL) {
					nowCapa = tempBag->now_capacity;
					nowBag = tempBag;
				}
			}
		}
		return nowBag;
	}
}
void maxProfit(KnapsackBag* bag) {
	KnapsackBag* newBag = ShallowCopyBag(bag);
	displaySelectedItem(_maxProfit(newBag,0));
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
	pReturn = (KnapsackItem*)malloc(sizeof(KnapsackItem)*count);
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
		pReturn->now_capacity = n;
		pReturn->item_count = count;
		KnapsackItem* items = getItems(count);
		if (items != NULL) pReturn->items = items;
	}
	return pReturn;
}