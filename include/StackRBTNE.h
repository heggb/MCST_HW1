#ifndef STACKRBTNE_H
#define STACKRBTNE_H

#include <stdbool.h>
#include "RBTreeNodesElement.h"

typedef struct StackRBTNE StackRBTNE; //Стек, в котором хранятся элементы красно-чёрного дерева

struct StackRBTNE
{
    RBTreeNodesElement** RBTNEs;
    uint32_t capacity;
    int64_t top;
};

StackRBTNE* createStackRBTNE (uint32_t capacity);
void pushStackRBTNE (StackRBTNE* SRBTNE, RBTreeNodesElement* RBTNE);
RBTreeNodesElement* popStackRBTNE (StackRBTNE* SRBTNE);
bool isEmptyStackRBTNE (StackRBTNE* SRBTNE);
bool isFullStackRBTNE (StackRBTNE* SRBTNE);
void freeStackRBTNE(StackRBTNE* SRBTNE);

#endif