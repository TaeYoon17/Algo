#ifndef _CLOSEST_
#define _CLOSEST_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct _point {
	int x, y;
}Point;

float closestPair(Point points[], int count);
float closesetRecur(Point points[], int end);
float minThreePoint(Point points[]);
float minTwoPoint(Point points[]);
float getDistance(Point fromPoints, Point toPoints);

float getShortPath(float a, float b);
void pathSort(Point* points, int count);
void qPathSortRecur(Point points[], int start, int end);
int qPathSortPivot(Point arr[], int start, int end);
void displayPoints(Point points[], int count);
#endif