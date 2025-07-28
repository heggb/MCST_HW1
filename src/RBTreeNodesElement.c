#include "RBTreeNodesElement.h"
#include "RBTreeNodes.h"

RBTreeNodesElement* createRBTreeNodesElement (RBTreeNodes* RBTN, Node* n)
{
    RBTreeNodesElement* new_RBTNE = (RBTreeNodesElement*)malloc(sizeof(RBTreeNodesElement));
    new_RBTNE->node = n;
    new_RBTNE->color = RED;
    new_RBTNE->parent = new_RBTNE->left = new_RBTNE->right = RBTN->nil;
    (n->count_ptr)++;
    return new_RBTNE;
}
void freeRBTreeNodesElement(RBTreeNodesElement* RBTNE)
{
    //if (RBTNE == NULL) return;
    Node* buff_node = RBTNE->node;
    free (RBTNE);
    if (--(buff_node->count_ptr) < 1)
    {
        freeNode(buff_node);
    }
}