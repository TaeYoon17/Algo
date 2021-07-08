#ifndef _LINKEDGRAPH_
#define _LINKEDGRAPH_
#define DIRECT_TYPE 0
#define UNDIRECT_TYPE 1
#include "linkedlist.h";
typedef struct LinkedGraphType {
	int graphType;
	int nodeCount;
	LinkedList** ppAdjEdge;
}LinkedGraph;

LinkedGraph* createLinkedGraph(int type, int size);
int checkVertexValid(LinkedGraph* graph, int node);
int addEdgeInternal(LinkedGraph* graph, int fromNode, int toNode, int weight);
int removeEdgeInternal(LinkedGraph* graph, int fromNode, int toNode);
int addEdge(LinkedGraph* graph, int fromNode, int toNode, int weight);
int removeEdge(LinkedGraph* graph, int fromNode, int toNode);

#endif