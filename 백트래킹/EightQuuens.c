/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define blockCount 8

void displayGrid(int colIdx[]){
	for (int i = 0; i < blockCount; i++) {
		for (int j = 0; j < blockCount; j++) {
			if (j == colIdx[i]) printf("O");
			else printf("X");
		}
		printf("\n");
	}
	printf("\n");
}

int ThisPathOkay(int colIdx[],int row,int newCol) {
	for (int i = 0; i < row; i++) {
		if (colIdx[i] == newCol) return 0;
		int a = i, b = colIdx[a];
		int rowLen = abs(row - a), colLen = abs(newCol - b);
		if (rowLen == colLen) return 0;
	}
	return 1;
}
int isFullRow(int row) {
	return row == blockCount - 1 ? 1: 0;
}
void Queen_BackTracking(int colIdx[],int row) {
	for (int i = 0; i < blockCount; i++) {
		if (ThisPathOkay(colIdx,row,i)) {
			colIdx[row] = i;
			if (isFullRow(row)) {
				displayGrid(colIdx);
			}
			else {
				Queen_BackTracking(colIdx, row + 1);
			}
		}
		else {
			//printf("Already have path");
			//displayGrid(colIdx);
		}
	}
}

void startQueens(int grid[]) {
	Queen_BackTracking(grid, 0);
}
int main() {
	int grid[blockCount] = {-1};
	startQueens(grid);
	return 0;
}
*/