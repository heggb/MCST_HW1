#include "Edge.h"

Edge* createEdge (Node* node_from, Node* node_to, uint32_t value)
{
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->value = value;
    new_edge->from = node_from;
    new_edge->to = node_to;
    new_edge->count_ptr = 0;
    new_edge->reverse_value = 0;
    return new_edge;
}