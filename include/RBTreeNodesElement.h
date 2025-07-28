#ifndef RBTREENODESELEMENT_H
#define RBTREENODESELEMENT_H

#include "Node.h"

typedef struct RBTreeNodesElement RBTreeNodesElement; //Элемент красно-чёрного дерева, в котором хранятся узлы 
typedef enum {BLACK, RED} Color; //Цвета для окрашивания в дереве
typedef struct RBTreeNodes RBTreeNodes;

struct RBTreeNodesElement
{
    Node* node;
    Color color;
    RBTreeNodesElement *parent, *left, *right;
};

RBTreeNodesElement* createRBTreeNodesElement (RBTreeNodes* RBTN, Node* n);
void freeRBTreeNodesElement(RBTreeNodesElement* RBTNE);

#endif