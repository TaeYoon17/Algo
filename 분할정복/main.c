#include <stdio.h>
#include <stdlib.h>
#include "closest.h"
int main() {
	Point points[] = { {2,5},{15,30},{5,2},{15,10},{10,5} };

	int count = sizeof(points) / sizeof(Point);
	float shortest = closestPair(points, count);
	printf("shortest: %f", shortest);
}