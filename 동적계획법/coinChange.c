#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

typedef struct coinItem {
	int value;
	int selected;
}coinItem;
void displayItems(coinItem items[],int count) {
	for (int i = 0; i < count; i++) {
		printf("value: %d", items[i].value);
	}
}
coinItem* createItemsInfo(int n) {
	int i = 0;
	coinItem* pReturn = (coinItem*)malloc(sizeof(coinItem) * n);
	if (pReturn != NULL) {
		for (i = 0; i < n; i++) {
			printf("얼마짜리 동전인가?: ");
			scanf("%d", &pReturn[i].value);
			pReturn[i].selected = 0;
			if (i != 0 && pReturn[i].value<pReturn[i-1].value) {
				coinItem temp = { 0 };
				temp = pReturn[i];
				pReturn[i] = pReturn[i - 1];
				pReturn[i - 1] = temp;
			}
		}
	}
	else {
		printf("매우 큰 에러!!");
	}
	return pReturn;
}

int getChangeDC(coinItem items[],int count,int changeMoney){
	if (changeMoney <= 0) {
		return 0;
	}
	else {
		int result = 9999,temp=0;
		for (int i = 0; i < count; i++) {
			int afterChange = changeMoney - items[i].value;
			if (afterChange < 0) {
				break;
			}
			else {
				temp= 1+getChangeDC(items, count, afterChange);
				if (temp < result)result = temp;
			}
		}
		return result;
	}
}

int getChangeDP(coinItem items[], int count, int changeMoney){
	int ret = 0;
	int *TotalCount = (int*)malloc(sizeof(int) * (changeMoney+1));
	memset(TotalCount,0,sizeof(int)*changeMoney);
	for (int i = 1; i <= changeMoney; i++) {
		int min = 9999;
		for (int j = 0; j < count; j++) {
			if (i >= items[j].value) {
			if (min > TotalCount[i - items[j].value]+1)
				min = TotalCount[i - items[j].value]+1;
			}
		}
		TotalCount[i] = min;
	}
	ret = TotalCount[changeMoney];
	free(TotalCount);
	return ret;
}

int main() {
	int changeMoney,count;
	int result = 0;
	printf("거스름돈은 얼마인가?: ");
	scanf("%d", &changeMoney);
	printf("동전의 개수는 몇개인가?: ");
	scanf("%d", &count);
	coinItem* items = createItemsInfo(count);
	//displayItems(items,count);
	if (items != NULL) {
		result = getChangeDC(items,count,changeMoney);
		printf("%d\n", result);
		result = getChangeDP(items,count,changeMoney);
		printf("%d", result);
		free(items);
	}
	return 0;
}