#include "PriorityQueueNodes.h"

void swap (Node** n1, Node** n2)
{
    Node* temp_node = *n1;
    *n1 = *n2;
    *n2 = temp_node;
}

void heapifyUp(PriorityQueueNodes* PQN, uint32_t index) {
    while (index > 0) {
        uint32_t parent = (index - 1) / 2;
        if (PQN->heap[index]->distance >= PQN->heap[parent]->distance) {
            break;
        }
        swap(&(PQN->heap[index]), &(PQN->heap[parent]));
        index = parent;
    }
}

void heapifyDown(PriorityQueueNodes* PQN, uint32_t index) {
    while (true)
    {
        uint32_t smallest = index;
        uint32_t left = 2 * index + 1;
        uint32_t right = 2 * index + 2;

        if (left < PQN->size && PQN->heap[left]->distance < PQN->heap[smallest]->distance)
        {
            smallest = left;
        }

        if (right < PQN->size && PQN->heap[right]->distance < PQN->heap[smallest]->distance)
        {
            smallest = right;
        }

        if (smallest == index) 
        {
            break;    
        }

        swap(&PQN->heap[index], &PQN->heap[smallest]);
        index = smallest;
    }
}

PriorityQueueNodes* createPriorityQueueNodes (uint32_t capacity)
{
    PriorityQueueNodes* PQN = (PriorityQueueNodes*)malloc(sizeof(PriorityQueueNodes));

    PQN->heap = (Node**)malloc(capacity* sizeof(Node*));
    PQN->capacity = capacity;
    PQN->size = 0;
    return PQN;

}

bool isEmptyPriorityQueueNodes (PriorityQueueNodes* PQN)
{
    return PQN->size < 1;
}

bool isFullPrioorityQueueNodes (PriorityQueueNodes* PQN)
{
    return PQN->size == PQN->capacity;
}

void enPriorityQueueNodes (PriorityQueueNodes* PQN, Node* n)
{
    PQN->heap[PQN->size] = n;
    heapifyUp(PQN, PQN->size);
    PQN->size++;
}

Node* dePriorityQueueNodes (PriorityQueueNodes* PQN)
{
    Node* min_node = PQN->heap[0];
    PQN->heap[0] = PQN->heap[--PQN->size];
    heapifyDown(PQN, 0);
    return min_node;
}

void freePriorityQueueNodes (PriorityQueueNodes* PQN)
{
    free(PQN->heap);
    free(PQN);
}