#include <stdio.h>
#include <stdlib.h>

typedef struct _point {
	int x, y;
}Point;

void displayPoints(Point points[],int count) {
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%d ",points[i].x);
	}
}
int qPathSortPivot(Point arr[],int start,int end){
	int pivot = end;
	int right = end;
	int left = start;
	Point temp = { 0,0 };
	while (left < right) {
		while ((left < right) && (arr[left].x < arr[pivot].x)) {
			left++;
		}
		while ((left < right) && (arr[right].x >= arr[pivot].x)) {
			right--;
		}
		if (left < right) {
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
	}
	printf("%d %d\n", left, right);
	temp = arr[pivot];
	arr[pivot]=arr[left];
	arr[left]=temp;
	return left;
}
void qPathSortRecur(Point points[],int start,int end){
	if (start < end) {
		int pivot = qPathSortPivot(points,start,end);
		qPathSortRecur(points, start, pivot - 1);
		qPathSortRecur(points, pivot+1, end);
	}
}
void pathSort(Point* points,int count) {
	qPathSortRecur(points,0,count-1);
}

int closesetRecur(Point points[],int count) {
	switch (count) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

int closestPair(Point points[], int count) {
	pathSort(points, count);
	return closestRecur(points,count);
}

int main() {
	Point points[] = { {2,5},{15,30},{5,2},{15,10},{10,5} };

	int count = sizeof(points) / sizeof(Point);

	int shortest = closestPair(points, count);
}