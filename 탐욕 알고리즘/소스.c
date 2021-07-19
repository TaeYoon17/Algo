#define _CRT_SECURE_NO_WARNINGS 
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

void displaySortItems(KnapsackItem items[],int count) {
	int i = 0;
	printf("\t이름\t무게\t가치\t비율\n");
	for (i = 0; i < count; i++) {
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",i, items[i].name,items[i].weight,items[i].profit,items[i].profit/items[i].weight);
	}
	return;
}
void displaySortBag(KnapsackBag *bag) {
	displaySortItems(bag->items, bag->item_count);
	return;
}

void maxProfit(KnapsackBag *bag) {
	int i = 0, count = bag->item_count;
	int nowCapacity = bag->max_capacity;
	int maxProfit = 0;
	for (i = 0; i < count; i++) {
		if (nowCapacity > bag->items[i].weight) {
			maxProfit += bag->items[i].profit;
			nowCapacity -= bag->items[i].weight;
			bag->items[i].selected = bag->items[i].weight;
		}
		else {
			maxProfit += nowCapacity / bag->items[i].weight * bag->items[i].profit;
			bag->items[i].selected = nowCapacity;
			break;
		}
	}
	printf("최대 이익: %d\n", maxProfit);
	printf("이름\t선택된 무게\t전체 무게\n");
	for (i = 0; i < count; i++) {
		printf("%s\t%.2f\t\t%.2f\n", bag->items[i].name, bag->items[i].selected, bag->items[i].weight);
	}
	return;
}

void changeCapacity(KnapsackBag* bag) {
	double n;
	printf("가방 용량을 입력하세요:");
	scanf("%lf", &n);
	if (bag != NULL)bag->max_capacity = n;
	maxProfit(bag);
}

int getPivot(KnapsackItem items[],int start,int end) {
	int pivot = end;
	int right = end;
	int left = start;
	double leftRatio = 0, rightRatio = 0, pivotRatio = 0;
	KnapsackItem temp = { 0 };
	while (left < right) {
		leftRatio = items[left].profit / items[left].weight;
		rightRatio = items[right].profit / items[right].weight;
		pivotRatio = items[pivot].profit / items[pivot].weight;
		while((leftRatio>pivotRatio)&&(left<right)){
			left++;
			leftRatio = items[left].profit / items[left].weight;
		}
		while((rightRatio<=pivotRatio)&&(left<right)){
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

void quickSortItems(KnapsackItem items[],int start,int end){
	int pivot = 0;
	if (start < end) {
		pivot=getPivot(items,start,end);
		quickSortItems(items, start, pivot-1);
		quickSortItems(items, pivot+1, end);
	}
}

KnapsackItem* getItems(int count) {
	KnapsackItem* pReturn = NULL;
	int i = 0;
	pReturn = (KnapsackItem*)malloc(sizeof(KnapsackItem));
	if (pReturn != NULL) {
		for (i = 0; i < count; i++) {
			double weight, profit;
			printf("%d번째 물건의 이름:", i + 1);
			scanf("%s", pReturn[i].name);
			getchar();
			printf("물건의 무게와 금액: ");
			scanf("%lf %lf", &weight, &profit);
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
		quickSortItems(pReturn,0,count-1);
	}
	return pReturn;
}
KnapsackBag* createBag() {
	int count = 0;
	double n = 0;
	KnapsackBag* pReturn = NULL;
	pReturn = (KnapsackBag*)malloc(sizeof(KnapsackBag));
	printf("가방 전체 용량을 입력하세요: ");
	scanf("%lf", &n);
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

int main() {
	KnapsackBag *bag=createBag();
	displaySortBag(bag);
	changeCapacity(bag);
	return 0;
}