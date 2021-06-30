/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void print(int value[], int length) {
	int i = 0;
	for (i = 0; i < length; i++) printf("%d ", value[i]);
}

void mergeRecursion(int arr[], int buffer[], int start, int end, int middle) {
	int i = start, j = middle + 1, k = start;
	while(i<=middle && j<=end){
		if (arr[i] <= arr[j]) {
			buffer[k] = arr[i];
			i++;
		}
		else {
			buffer[k] = arr[j];
			j++;
		}
		k++;
	}
	
	for (i; i <= middle; i++) buffer[k++] = arr[i];
	for (j; j <= end; j++) buffer[k++] = arr[j];
	for (i = start; i <= end; i++) arr[i] = buffer[i];
}

void mergeSort(int arr[],int buffer[],int start,int end){
	int middle = 0;
	if (start < end) {
		middle = (start + end) / 2;
		mergeSort(arr, buffer, start, middle);
		mergeSort(arr, buffer, middle + 1, end);
		mergeRecursion(arr, buffer, start, end, middle);
	}
}

int main() {
	int arr[8] = { 80,75,10,60,15,49,12,25 };
	int* pBuffer = (int*)malloc(sizeof(int) * 8);
	mergeSort(arr,pBuffer,0,7);
	print(arr, 8);
}*/