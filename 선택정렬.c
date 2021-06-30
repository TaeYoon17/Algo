/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void print(int value[],int length) {
	int i = 0;
	for (i = 0; i < length; i++) printf("%d ", value[i]);
}
void selectedSort(int value[],int length){
	int i, j,min,temp;
	for (i = 0; i < length-1; i++) {
		min = i;
		for (j = i+1; j < length; j++) {
			if (value[min] > value[j]) min = j;
		}
		temp = value[i];
		value[i] = value[min];
		value[min] = temp;
	}
}

int main() {
	int arr[8] = { 80,75,10,60,15,49,12,25 };
	selectedSort(arr,8);
	print(arr,8);
}*/