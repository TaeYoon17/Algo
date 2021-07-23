#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "zerooneKnapsack.h"
int main() {
	KnapsackBag* bag = createBag();
	displaySortBag(bag);
	maxProfit(bag);
}