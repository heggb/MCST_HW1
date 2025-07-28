#include "ListEdges.h"
#include "Node.h"

ListEdges* createListEdges()
{
    ListEdges* new_LE = (ListEdges*)malloc(sizeof(ListEdges));
    new_LE->count = 0;
    new_LE->head = NULL;
    new_LE->tail = NULL;
    return new_LE;
}

void insertBeforeHead(ListEdges* LE, ListEdgesElement* LEE)
{
    LEE->next = LE->head;
    if (LE->head != NULL)
    {
        LE->head->prev = LEE;
    }
    else
    {
        LE->tail = LEE;
    }
    LE->head = LEE;
    LEE->prev = NULL;
}

void addEdge(ListEdges* LE, Edge* e)
{
    ListEdgesElement* new_LEE = createListEdgesElement(e);
    insertBeforeHead (LE, new_LEE);
    LE->count++;
}

void freeListEdges(ListEdges* LE)
{
    ListEdgesElement* cur_LLE = LE->head;
    while (cur_LLE)
    {
        ListEdgesElement* del_LLE = cur_LLE;
        cur_LLE = cur_LLE->next;
        freeListEdgesElement (del_LLE);
    }
    free(LE);
}

ListEdgesElement* findListEdgesElement (ListEdges* LE, Node* node_from, Node* node_to)
{
    if (!LE || !LE->head) return NULL;

    ListEdgesElement* result = NULL;
    for (ListEdgesElement* cur_LEE = LE->head; cur_LEE && !result; cur_LEE = cur_LEE->next)
    {
        if (cur_LEE->edge->from == node_from && cur_LEE->edge->to == node_to)
        {
            result = cur_LEE;
        }
    }
    return result;
}

Edge* findEdge (Node* node_from, Node* node_to)
{
    ListEdgesElement* result = NULL;
    uint32_t count_node_from_out_edges = node_from->out_edges->count;
    uint32_t count_node_to_in_edges = node_to->in_edges->count;

    //Поиск ребра осуществляется в списках входящих/исходящих рёбер той вершины, в которой их длина меньше всего, но не = 0
    if (count_node_from_out_edges > 0 && count_node_from_out_edges < count_node_to_in_edges)
    {
        result = findListEdgesElement(node_from->out_edges, node_from, node_to);
    }
    else if (count_node_to_in_edges > 0)
    {
        result = findListEdgesElement(node_to->in_edges, node_from, node_to);
    }
    if (!result) return NULL;
    return result->edge;
}

void deleteEdge (ListEdges* LE, ListEdgesElement* del_LEE)
{
    if (!del_LEE) return;

    if (del_LEE->prev)
    {
        del_LEE->prev->next = del_LEE->next;
    }
    else
    {
        LE->head = del_LEE->next;
    }

    if (del_LEE->next)
    {
        del_LEE->next->prev = del_LEE->prev;
    }
    else
    {
        LE->tail = del_LEE->prev;
    }

    freeListEdgesElement(del_LEE);

    (LE->count)--;
}

void printEdges (ListEdges* LE)
{
    if(LE->count < 1) return;

    for (ListEdgesElement* LLE = LE->head; LLE; LLE = LLE->next)
    {
        printf ("%s->%s(%d) ", LLE->edge->from->id, LLE->edge->to->id, LLE->edge->value);
    }
    printf("\n");
}

