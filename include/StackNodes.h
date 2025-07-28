#ifndef STACKNODES_H
#define STACKNODES_H

#include <stdbool.h>
#include "RBTreeNodesElement.h"


typedef struct StackNodes StackNodes; 

struct StackNodes
{
    Node** nodes;
    uint32_t capacity;
    int64_t top;
};

StackNodes* createStackNodes (uint32_t capacity);
void pushStackNodes (StackNodes* SN, Node* n);
Node* popStackNodes (StackNodes* SN);
bool isEmptyStackNodes (StackNodes* SN);
bool isFullStackNodes (StackNodes* SN);
void freeStackNodes (StackNodes* SN);

#endif