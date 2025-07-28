#ifndef RBTREENODES_H
#define RBTREENODES_H

#include <stdio.h>
#include "RBTreeNodesElement.h"
#include "StackRBTNE.h"
#include "StackNodes.h"
#include "ListEdgesElement.h"
#include "ListEdges.h"
#include "PriorityQueueNodes.h"


typedef struct RBTreeNodes RBTreeNodes;

struct RBTreeNodes 
{
    uint32_t count;
    RBTreeNodesElement *root, *nil;
};

RBTreeNodes* createRBTreeNodes();
void addNode(RBTreeNodes* RBTN, Node* n);
RBTreeNodesElement* findRBTreeNodesElement (RBTreeNodes* RBTN, const char* name_node);
Node* findNode (RBTreeNodes* RBTN, const char* name_node);
StackNodes* getRPO(RBTreeNodes* RBTN, RBTreeNodesElement* start_RBTNE);
PriorityQueueNodes* Dijkstra (RBTreeNodes* RBTN, Node* n);
RBTreeNodesElement* findWhiteRBTNE (RBTreeNodes* RBTN);
void deleteNode (RBTreeNodes* RBTN, RBTreeNodesElement* RBTNE);
void printNodes (RBTreeNodes* RBTN);
void freeRBTreeNodes (RBTreeNodes* RBTN);

#endif