#ifndef _COIN_CHANGE_
#define _COIN_CHANGE_
typedef struct coinItem {
	int value;
	int selected;
}coinItem;

void displayItems(coinItem items[], int count);
coinItem* createItemsInfo(int n);
int getChangeDC(coinItem items[], int count, int changeMoney);
int getChangeDP(coinItem items[], int count, int changeMoney);

#endif