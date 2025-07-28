#include "StackRBTNE.h"

StackRBTNE* createStackRBTNE (uint32_t capacity)
{
    StackRBTNE* new_SRBTNE = (StackRBTNE*)malloc(sizeof(StackRBTNE));
    new_SRBTNE->RBTNEs = (RBTreeNodesElement**)malloc(capacity * sizeof(RBTreeNodesElement*));
    new_SRBTNE->capacity = capacity;
    new_SRBTNE->top = -1;
    return new_SRBTNE;
}

void pushStackRBTNE (StackRBTNE* SRBTNE, RBTreeNodesElement* RBTNE)
{
    SRBTNE->RBTNEs[++(SRBTNE->top)] = RBTNE;
}

RBTreeNodesElement* popStackRBTNE (StackRBTNE* SRBTNE)
{
    if (isEmptyStackRBTNE(SRBTNE)) return NULL;

    return SRBTNE->RBTNEs[(SRBTNE->top)--];
}

bool isEmptyStackRBTNE (StackRBTNE* SRBTNE)
{
    return SRBTNE->top < 0;
}

bool isFullStackRBTNE (StackRBTNE* SRBTNE)
{
    return SRBTNE->top + 1 == SRBTNE->capacity;
}

void freeStackRBTNE(StackRBTNE* SRBTNE)
{
    free (SRBTNE->RBTNEs);
    free (SRBTNE);
}