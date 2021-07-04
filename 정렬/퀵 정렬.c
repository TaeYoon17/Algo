/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void print(int value[], int length) {
	int i = 0;
	for (i = 0; i < length; i++) printf("%d ", value[i]);
}

int validateSort(int value[], int start, int end) {
	int left = start;int right = end;
	int pivot = end;int temp;
	while (left < right) {
		while ((value[left]<value[pivot])&&(left < right)) left++;
		while ((value[right]>=value[pivot])&&(left < right)) right--;
		if (left < right) {
			temp = value[right];
			value[right] = value[left];
			value[left] = temp;
		}
	}
	temp = value[pivot];
	value[pivot] = value[right];
	value[right] = temp;
	return right;
}
void quickSort(int value[],int start,int end) {
	int pivot = 0;
	if (start < end) {
		pivot = validateSort(value, start, end);
		quickSort(value, start, pivot - 1);
		quickSort(value, pivot + 1, end);
	}
}

int main() {
	int arr[8] = { 80,75,10,60,15,49,12,25 };
	quickSort(arr, 0, 7);
	print(arr, 8);
}*/