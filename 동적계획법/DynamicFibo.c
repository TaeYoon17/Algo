/*#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

int fibo(int n){
	int *arr = (int*)malloc(sizeof(int) * n);
	if (arr != NULL) {
		arr[0] = 1;
		arr[1] = 1;
		for (int i = 2; i < n; i++) {
			arr[i] = arr[i - 1] + arr[i - 2];
		}
		int ret = arr[n - 1];
		free(arr);
		return ret;
	}
	else {
		printf("Error!!");
		return -1;
	}
}

int main() {
	int n;
	scanf("%d", &n);

	printf("%d",fibo(n));
}*/