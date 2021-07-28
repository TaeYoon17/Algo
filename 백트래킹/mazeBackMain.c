#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define HEIGHT 8
#define WEIGHT 8
enum PosStatus{NOT_VISIT,WALL,VISIT,NO_WAY};
enum Direction {RIGHT,UP,LEFT,DOWN};
typedef struct Position {
	int x, y;
}Position;
typedef struct PosStack {
	Position* arr;
	int maxSize;
	int currentSize;
}PosStack;
int isEmptyStack(PosStack* st) {
	return st->currentSize < 0 ? 1 : 0;
}
int isFullStack(PosStack *st) {
	return st->currentSize+1 == st->maxSize ? 1 : 0;
}
void pushStack(PosStack *st,Position data) {
	if (isFullStack(st)) {
		printf("모든 좌표 순회\n");
		return 0;
	}
	else {
		st->arr[++(st->currentSize)] = data;
	}
}
Position popStack(PosStack* st) {
	Position temp = { -1,-1 };
	if (isEmptyStack(st)) {
		printf("어떤 좌표도 없음");
	}
	else {
		temp = st->arr[st->currentSize];
		st->arr[st->currentSize].x=-1 ;
		st->arr[st->currentSize].y=-1;
		st->currentSize--;
	}
	return temp;
}
void displayStack(PosStack *st) {
	printf("StackNow=>");
	for (int i = 0; i < st->currentSize; i++) {
		printf("x: %d y: %d ",st->arr[i].x,st->arr[i].y );
	}
	printf("\n");
}
PosStack* createStack() {
	PosStack* st = NULL;
	st = (PosStack*)malloc(sizeof(PosStack));
	if (st != NULL) {
		st->maxSize = HEIGHT * WEIGHT;
		st->currentSize = -1;
		st->arr = (Position*)malloc(sizeof(Position) * st->maxSize);
		memset(st->arr,0,sizeof(Position)*st->maxSize);
	}
	else {
		printf("스택 생성 오류!");
	}
	return st;
}

int isRightCoor(int mazeArray[HEIGHT][WEIGHT],Position coordinate) {
	return 0 <= coordinate.x && coordinate.x < HEIGHT && 0 <= coordinate.y && coordinate.y < WEIGHT&&mazeArray[coordinate.x][coordinate.y]== NOT_VISIT
		? 1 : 0;
}
int isNowSameEnd(Position now,Position end) {
	return now.x == end.x && now.y == end.y ? 1 : 0;
}

void printMaze(int mazeArray[HEIGHT][WEIGHT],PosStack *st) {
	displayStack(st);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WEIGHT; j++) {
			switch (mazeArray[i][j]) {
			case NOT_VISIT:
				printf("O");
				break;
			case WALL:
				printf("X");
				break;
			case VISIT:
				printf("$");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}

Position goDirection(Position now, int dir) {
	switch (dir) {
	case RIGHT: now.y++; break;
	case LEFT: now.y--; break;
	case UP: now.x++; break;
	case DOWN: now.x--; break;
	default: printf("잘못된 방향지시"); break;
	}
	return now;
}

void MazeBackRecur(int mazeArray[HEIGHT][WEIGHT],Position now,Position end,PosStack *st) {
	if (isRightCoor(mazeArray,now)) {
		pushStack(st, now);
		mazeArray[now.x][now.y] = VISIT;
		if (isNowSameEnd(now, end)) {
			printMaze(mazeArray, st);
		}
		else {
			for (int i = 0; i < 4; i++) {
				int newMaze[HEIGHT][WEIGHT];
				for (int i = 0; i < HEIGHT; i++) {
					for (int j = 0; j < WEIGHT; j++) {
						newMaze[i][j] = mazeArray[i][j];
					}
				}
				PosStack* newSt = createStack();
				newSt->currentSize = st->currentSize;
				newSt->maxSize = st->maxSize;
				for (int i = 0; i <= newSt->currentSize; i++) {
					newSt->arr[i].x = st->arr[i].x;
					newSt->arr[i].y = st->arr[i].y;
				}
				MazeBackRecur(newMaze,goDirection(now,i),end,newSt);
			}
			free(st->arr);
			free(st);
		}
	}
}
void startMazeBack(int mazeArray[HEIGHT][WEIGHT],Position startCoor,Position endCoor) {
	if (isRightCoor(mazeArray,startCoor) && isRightCoor(mazeArray,endCoor)) {
		PosStack* stack = createStack();
		MazeBackRecur(mazeArray,startCoor,endCoor,stack);
		free(stack->arr);
		free(stack);
	}
	else {
		printf("좌표 입력 오류\n");
	}
}

int main() {
	int mazeArray[HEIGHT][WEIGHT] = {
		{0,0,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,0,1,1,1,1},
		{1,1,1,0,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,0}
	};
	Position startCoor = { 0,0 };
	Position endCoor = { 7,7 };
	startMazeBack(mazeArray, startCoor, endCoor);
}