#ifndef _TSP_BACKTRACKING_
#define _TSP_BACKTRACKING_
#define NODE_COUNT 4
#include <limits.h>

int checkValiPath(int checkPath[], int nowCount);
void printPath(int optimalPath[]);
void _tsp_Back(int costGraph[][NODE_COUNT], int optimalPath[], int checkPath[],
    int nowCount, int nowCost, int* minCost);
void tsp_Back(int costGraph[][NODE_COUNT], int* optimalPath, int* minCost);

#endif
