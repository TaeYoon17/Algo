#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

int main(int argc, char* argv[])
{
    BTree* pTree = NULL;
    BTreeNodeData* pSearchData = NULL;
    int key = 0;

    BTreeNodeData eA = { 9, 'A' };
    BTreeNodeData eB = { 12, 'B' };
    BTreeNodeData eC = { 19, 'C' };
    BTreeNodeData eD = { 39, 'D' };
    BTreeNodeData eE = { 65, 'E' };
    BTreeNodeData eF = { 53, 'F' };
    BTreeNodeData eG = { 63, 'G' };
    BTreeNodeData eH = { 89, 'H' };
    BTreeNodeData eI = { 48, 'I' };
    BTreeNodeData eJ = { 36, 'J' };

    pTree = createBTree();
    if (pTree != NULL)
    {
        addDataBT(pTree, eA);
        addDataBT(pTree, eB);
        addDataBT(pTree, eC);
        addDataBT(pTree, eD);
        printf("\n01-자료 추가중\n");
        displayBTree(pTree);

        addDataBT(pTree, eE);
        printf("\n02-자료 추가중\n");
       displayBTree(pTree);
    }
}
