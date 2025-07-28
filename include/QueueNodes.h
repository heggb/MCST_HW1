#ifndef QUEUENODES_H
#define QUEUENODES_H

#include <stdbool.h>
#include "Node.h"

typedef struct QueueNodes QueueNodes; 

struct QueueNodes
{
    Node** nodes;
    uint32_t capacity, count;
    int64_t front, top;
};

QueueNodes* createQueueNodes (uint32_t capacity);
bool isEmptyQueueNodes (QueueNodes* QN);
bool isFullQueueNodes (QueueNodes* QN);
void enQueueNodes (QueueNodes* QN, Node* n);
Node* deQueueNodes (QueueNodes* QN);
void freeQueueNodes (QueueNodes* QN);

#endif