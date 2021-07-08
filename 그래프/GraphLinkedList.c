#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph.h"
#include "graphDFS.h"
void traverseBFS(LinkedGraph*graph,LinkedList*Node,int startVertex){
	
}

int main() {
	LinkedGraph* graph = createLinkedGraph(DIRECT_TYPE, 6);
	addEdge(graph, 0, 1, 2);
	addEdge(graph, 0, 2, 4);
	addEdge(graph, 1, 2, 1);
	addEdge(graph, 2, 0, 4);
	addEdge(graph, 2, 3, 7);
	addEdge(graph, 3, 2, 5);
	addEdge(graph, 3, 4, 2);
	addEdge(graph, 3, 5, 6);
	addEdge(graph, 4, 5, 3);
	addEdge(graph, 5, 3, 6);
	displayGraph(graph);
	traverseDFS(graph,2);
}