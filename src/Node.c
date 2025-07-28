#include "Node.h"
#include "ListEdges.h"

Node* createNode (const char* name)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = strdup(name);
    new_node->in_edges = createListEdges();
    new_node->out_edges = createListEdges();
    //new_node->state = WHITE_S;
    new_node->count_ptr = 0;
    new_node->index = new_node->pre = new_node->post = 0;
    new_node->distance = UINT32_MAX;
    new_node->parent_node = NULL;
    return new_node;
}

void freeNode (Node* n)
{
    free((char*)(n->id));
    freeListEdges(n->in_edges);
    freeListEdges(n->out_edges);
    free(n);
}