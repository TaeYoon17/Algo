#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph.h"

int main() {
	LinkedGraph* pG3 = NULL;
	LinkedGraph* pMST1 = NULL;

	pG3 = createLinkedGraph(UNDIRECT_TYPE, 6);
	if (pG3 != NULL) {
		addEdge(pG3,0,1,4);
		addEdge(pG3, 0, 1, 4);
		addEdge(pG3, 0, 2, 3);
		addEdge(pG3, 1, 2, 2);
		addEdge(pG3, 2, 3, 1);
		addEdge(pG3, 3, 4, 1);
		addEdge(pG3, 3, 5, 5);
		addEdge(pG3, 4, 5, 6);

		printf("G3\n");
		displayGraph(pG3);
	}
	printf("Kruskal\n");
	pMST1 = mstKruskal(pG3);
	displayGraph(pMST1);
}