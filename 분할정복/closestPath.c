#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
float getShortPath(float a, float b) {
	return a < b ? a : b;
}

float getDistance(Point fromPoints, Point toPoints) {
	double x = fromPoints.x - toPoints.x;
	double y = fromPoints.y - toPoints.y;
	double distance = sqrt(x * x + y * y);
	return distance;
}
float minTwoPoint(Point points[]){
	return getDistance(points[0], points[1]);
}
float minThreePoint(Point points[]){
	float a = getDistance(points[0], points[1]);
	float b = getDistance(points[0], points[2]);
	float c = getDistance(points[1], points[2]);
	float temp = getShortPath(a, b);
	return getShortPath(temp, c);
}
float closesetRecur(Point points[], int end) {
	int mid = 0,i;
	float leftMin, rightMin, width,result=0,midMin;
	switch (end) {
	case 0:case 1:
		return 0;
	case 2:
		return minTwoPoint(points);
	case 3:
		return minThreePoint(points);
	default:
		mid = end / 2;
		leftMin = closesetRecur(points, mid);
		rightMin = closesetRecur(points+mid,end-mid);
		width = getShortPath(leftMin, rightMin);
		Point *sidePoints = (Point*)malloc(sizeof(Point)*mid);
		Point midPoint = points[mid];
		int sideCount = 0;
		if (sidePoints != NULL) {
			for (int i = 0; i < end; i++) {
				if (abs(points[i].x - midPoint.x) < width) {
					sidePoints[sideCount++] = points[i];
				}
			}
		}
		else {
			printf("¿¡·¯!!");
			return -1;
		}
		if (sideCount > 1) {
			midMin = closestPair(sidePoints, sideCount);
			result = getShortPath(width, midMin);
		}
		else result = width;
		free(sidePoints);
		return result;
	}
};

float closestPair(Point points[], int count) {
	pathSort(points, count);
	return closesetRecur(points,count);
}

int main() {
	Point points[] = { {2,5},{15,30},{5,2},{15,10},{10,5} };

	int count = sizeof(points) / sizeof(Point);
	float shortest = closestPair(points, count);
	printf("shortest: %f", shortest);
}