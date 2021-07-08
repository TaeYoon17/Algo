#include <stdio.h>
#include <stdlib.h>

#include "visitStack.h"

int FigureSameData(StackVX* stack, int node) {
	int i = 0;
	for (i = 0; i <= stack->top; i++) {
		if (node == stack->arr[i]) return 1;
	}
	return 0;
}
int isFullStack(StackVX* stack) {
	if (stack->top + 1 == stack->size) return 1;
	else return 0;
}
void pushSV(StackVX* stack, int node) {
	if (FigureSameData(stack, node)) return;
	if (isFullStack(stack)) {
		printf("FullStack\n");
		return;
	}
	stack->arr[++stack->top] = node;
}
int popSV(StackVX* stack) {
	int temp = -1;
	if (stack->top == -1) {
		printf("EmptyStack\n");
		return temp;
	}
	temp = stack->arr[stack->top--];
	stack->arr[stack->top + 1] = -1;
	return temp;
}
void traverseSV(StackVX* stack) {
	int i = 0;
	printf("traverseSV");
	for (i = 0; i <= stack->top; i++) {
		printf("%d ", stack->arr[i]);
	}
}
int getTop(StackVX* stack) {
	int temp = -1;
	temp = popSV(stack);
	pushSV(stack, temp);
	return temp;
}