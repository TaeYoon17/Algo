/*
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "coinChange.h"
int main() {
int changeMoney, count;
int result = 0;
printf("�Ž������� ���ΰ�?: ");
scanf("%d", &changeMoney);
printf("������ ������ ��ΰ�?: ");
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