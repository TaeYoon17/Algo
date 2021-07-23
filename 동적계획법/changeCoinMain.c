/*
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "coinChange.h"
int main() {
int changeMoney, count;
int result = 0;
printf("거스름돈은 얼마인가?: ");
scanf("%d", &changeMoney);
printf("동전의 개수는 몇개인가?: ");
scanf("%d", &count);
coinItem* items = createItemsInfo(count);
//displayItems(items,count);
if (items != NULL) {
	result = getChangeDC(items, count, changeMoney);
	printf("%d\n", result);
	result = getChangeDP(items, count, changeMoney);
	printf("%d", result);
	free(items);
}
return 0;
}
*/