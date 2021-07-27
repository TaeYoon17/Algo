#include <stdio.h>
#include <stdlib.h>
#include "tspBackTracking.h"
int main(void) {
    int costGraph[NODE_COUNT][NODE_COUNT] = {
      {0,10,15,20},
      {10,0,35,25},
      {15,35,0,30},
      {20,25,30,0}
    };
    int optimalPath[NODE_COUNT + 1] = { 0 };
    int minCost = 9999;
    tsp_Back(costGraph, optimalPath, &minCost);
    printPath(optimalPath);
    return 0;
}