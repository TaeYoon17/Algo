#ifndef _LINKEDLIST_
#define _LINKEDLIST_
typedef struct graphEdgeType {
	int toNodeID;
	int weight;
}graphEdge;
typedef struct LinkedListNodeType {
	graphEdge data;
	struct LinkedListNodeType* next;
}LinkedListNode;
typedef struct LinkedListType {
	LinkedListNode headerNode;
	int currentCount;
}LinkedList;

LinkedList* createLinkedList();
graphEdge* getLinkedListData(LinkedList* list, int position);
int addLinkedListData(LinkedList* list, int position, graphEdge data);
int removeLinkedListData(LinkedList* list, int position);
void deleteLinkedList(LinkedList *list);
#endif