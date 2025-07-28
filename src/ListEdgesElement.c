#include "ListEdgesElement.h"

ListEdgesElement* createListEdgesElement (Edge* e)
{
    if (!e) return NULL;

    ListEdgesElement* new_LEE = (ListEdgesElement*)malloc(sizeof(ListEdgesElement));
    if (!new_LEE) return NULL;
    new_LEE->edge = e;
    new_LEE->prev = new_LEE->next = NULL;
    (e->count_ptr)++;
    return new_LEE;
}

void freeListEdgesElement(ListEdgesElement* LEE)
{
    if (!LEE) return;

    Edge* buff_edge = LEE->edge;
    free (LEE);
    if (--(buff_edge->count_ptr) < 1)
    {
        free(buff_edge);
    }
}