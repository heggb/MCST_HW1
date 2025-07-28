#include "QueueNodes.h"

QueueNodes* createQueueNodes (uint32_t capacity)
{
    QueueNodes* new_QN = (QueueNodes*)malloc(sizeof(QueueNodes));
    new_QN->nodes = (Node**)malloc(capacity * sizeof(Node*));
    new_QN->capacity = capacity;
    new_QN->front = 0;
    new_QN->top = 0;
    new_QN->count = 0;
    
    return new_QN;
}

bool isEmptyQueueNodes (QueueNodes* QN)
{
    return QN->count == 0;
}

bool isFullQueueNodes (QueueNodes* QN)
{
    return QN->count == QN->capacity;
}

void enQueueNodes (QueueNodes* QN, Node* n)
{
    QN->nodes[QN->top] = n; 
    QN->top = (QN->top + 1) % QN->capacity;
    QN->count++;
    
}
Node* deQueueNodes (QueueNodes* QN)
{
    Node* node = QN->nodes[QN->front];
    QN->front = (QN->front + 1) % QN->capacity;
    QN->count--;
    return node;
}

void freeQueueNodes (QueueNodes* QN)
{
    free(QN->nodes);
    free(QN);
}