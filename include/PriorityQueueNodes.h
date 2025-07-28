#ifndef PRIORITIQUEUENODES_H
#define PRIORITIQUEUENODES_H

#include <stdbool.h>
#include "Node.h"

typedef struct PriorityQueueNodes PriorityQueueNodes;

struct PriorityQueueNodes
{
    Node** heap;
    uint32_t capacity, size;
};

PriorityQueueNodes* createPriorityQueueNodes (uint32_t capacity);
bool isEmptyPriorityQueueNodes (PriorityQueueNodes* PQN);
bool isFullPrioorityQueueNodes (PriorityQueueNodes* PQN);
void enPriorityQueueNodes (PriorityQueueNodes* PQN, Node* n);
Node* dePriorityQueueNodes (PriorityQueueNodes* PQN);
void freePriorityQueueNodes (PriorityQueueNodes* PQN);

#endif