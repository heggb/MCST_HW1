#ifndef LISTEDGESELEMENT_H
#define LISTEDGESELEMENT_H

#include "Edge.h"

typedef struct ListEdgesElement ListEdgesElement; //Элемент списка, в котором хранятся узлы

struct ListEdgesElement
{
    Edge* edge;
    ListEdgesElement *prev, *next;
};

ListEdgesElement* createListEdgesElement (Edge* e);
void freeListEdgesElement(ListEdgesElement* LEE);

#endif

