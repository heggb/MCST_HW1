#include "StackNodes.h"

StackNodes* createStackNodes (uint32_t capacity)
{
    StackNodes* new_SN = (StackNodes*)malloc(sizeof(StackNodes));
    new_SN->nodes = (Node**)malloc(capacity * sizeof(Node*));
    new_SN->capacity = capacity;
    new_SN->top = -1;
    return new_SN;
}

void pushStackNodes (StackNodes* SN, Node* n)
{
    //Реализация расширения при переполнении (потребовалось при тестировании алгоритма Тарьяна)
    if (isFullStackNodes(SN))
    {
        SN->capacity += 64;
        Node** new_nodes = realloc(SN->nodes, SN->capacity * sizeof(Node*));
        uint8_t counter = 0;
        while (!new_nodes && counter < 6)
        {
            SN->capacity /= 2;
            new_nodes = realloc(SN->nodes, SN->capacity * sizeof(Node*));
            counter++;
        }
        if (counter == 6)
        {
            exit (EXIT_FAILURE);
        } 
        SN->nodes = new_nodes;

    }
    SN->nodes[++(SN->top)] = n;
}

Node* popStackNodes (StackNodes* SN)
{
    if (isEmptyStackNodes(SN)) return NULL;

    return SN->nodes[(SN->top)--];
}

bool isEmptyStackNodes (StackNodes* SN)
{
    return SN->top < 0;
}

bool isFullStackNodes (StackNodes* SN)
{
    return SN->top + 1 == SN->capacity;
}

void freeStackNodes (StackNodes* SN)
{
    free(SN->nodes);
    free(SN);
}