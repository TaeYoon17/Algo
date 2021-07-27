#include "tspBackTracking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkValiPath(int checkPath[], int nowCount) {
    for (int i = 0; i < nowCount; i++) {
        if (checkPath[i] == checkPath[nowCount]) return 0;
    }
    return 1;
}
void printPath(int optimalPath[]) {
    for (int i = 0; i < NODE_COUNT + 1; i++) {
        printf("%d ", optimalPath[i]);
    }
    printf("\n");
}
void _tsp_Back(int costGraph[][NODE_COUNT], int optimalPath[], int checkPath[],
    int nowCount, int nowCost, int* minCost) {
    //printf("1");
    if (checkValiPath(checkPath, nowCount)) {
        int currentNode = checkPath[nowCount];
        if (nowCount == NODE_COUNT - 1) {
            int next_node = checkPath[0];
            checkPath[nowCount + 1] = next_node;
            nowCost += costGraph[currentNode][next_node];
            if (nowCost < *minCost) {
                *minCost = nowCost;
                memcpy(optimalPath, checkPath, sizeof(int) * NODE_COUNT);
                printPath(optimalPath);
            }
        }
        else {
            for (int i = 1; i < NODE_COUNT; i++) {
                int cost = nowCost + costGraph[currentNode][i];
                checkPath[nowCount + 1] = i;
                _tsp_Back(costGraph, optimalPath, checkPath, nowCount + 1, cost, minCost);
            }
        }
    }
}

void tsp_Back(int costGraph[][NODE_COUNT], int* optimalPath, int* minCost) {
    int checkPath[NODE_COUNT + 1] = { 0 };
    checkPath[0] = 0;
    _tsp_Back(costGraph, optimalPath, checkPath, 0, 0, minCost);
};
