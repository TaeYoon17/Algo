#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main() {
	char str[100] = "abcdeaaa";
	createTable(str);

	return 0;
}