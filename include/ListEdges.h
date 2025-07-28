#ifndef LISTEDGES_H
#define LISTEDGES_H

#include <stdio.h>

#include "ListEdgesElement.h"

typedef struct ListEdges ListEdges;
typedef struct Node Node;

struct ListEdges
{
    uint32_t count;
    ListEdgesElement *head, *tail;
};

ListEdges* createListEdges();
void addEdge (ListEdges* LE, Edge* e);
void freeListEdges(ListEdges* LE);
ListEdgesElement* findListEdgesElement (ListEdges* LE, Node* node_from, Node* node_to); //Поиск элемента списка, который указывает на искомое ребро, заданное начальной и конечнйо вершиной
Edge* findEdge (Node* node_from, Node* node_to);
void deleteEdge (ListEdges* LE, ListEdgesElement* del_LEE);
void freeListEdges(ListEdges* LE);
void printEdges (ListEdges* LE);


#endif