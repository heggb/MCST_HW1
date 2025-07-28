#include "RBTreeNodes.h"
// #include "StackRBTNE.h"
// #include "StackNodes.h"
// #include "ListEdgesElement.h"
// #include "ListEdges.h"
// #include "PriorityQueueNodes.h"

RBTreeNodesElement* findRBTreeNodesElement (RBTreeNodes* RBTN, const char* name_node)
{
    //if (!RBTN || !name_node) return NULL;

    RBTreeNodesElement* cur_RBTNE = RBTN->root;
    //int cmp = strcmp (name_node, cur_node->id);
    while (cur_RBTNE != RBTN->nil && strcmp (name_node, cur_RBTNE->node->id)!= 0)
    {
        if (strcmp (name_node, cur_RBTNE->node->id) < 0)
        {
            cur_RBTNE = cur_RBTNE->left;
        }
        else
        {
            cur_RBTNE = cur_RBTNE->right;
        }
    }
    
    return cur_RBTNE;  
}

Node* findNode (RBTreeNodes* RBTN, const char* name_node)
{
    RBTreeNodesElement* cur_RBTNE = findRBTreeNodesElement(RBTN, name_node);
    return cur_RBTNE == RBTN->nil ? NULL : cur_RBTNE->node;  
}

RBTreeNodes* createRBTreeNodes()
{
    RBTreeNodes* new_RBTN = (RBTreeNodes*)malloc(sizeof(RBTreeNodes));

    new_RBTN->nil = createRBTreeNodesElement(new_RBTN, createNode(""));
    new_RBTN->nil->color = BLACK;
    new_RBTN->count = 0;

    new_RBTN->nil->left = 
    new_RBTN->nil->right = 
    new_RBTN->nil->parent = 
    new_RBTN->nil;

    new_RBTN->root = new_RBTN->nil;
    return new_RBTN;
}

void leftRotate(RBTreeNodes* RBTN, RBTreeNodesElement* x) {
    RBTreeNodesElement* y = x->right;
    x->right = y->left;
    
    if (y->left != RBTN->nil) 
    {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == RBTN->nil) 
    {
        RBTN->root = y;
    } 
    else if (x == x->parent->left) 
    {
        x->parent->left = y;
    } 
    else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTreeNodes* RBTN, RBTreeNodesElement* y) {
    RBTreeNodesElement* x = y->left;
    y->left = x->right;
    
    if (x->right != RBTN->nil) 
    {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    
    if (y->parent == RBTN->nil) 
    {
        RBTN->root = x;
    } 
    else if (y == y->parent->right) 
    {
        y->parent->right = x;
    } 
    else 
    {
        y->parent->left = x;
    }
    
    x->right = y;
    y->parent = x;
}

void addFixup(RBTreeNodes* RBTN, RBTreeNodesElement* z) {
    while (z->parent != RBTN->nil && z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->left) 
        {
            RBTreeNodesElement* y = z->parent->parent->right;
            if (y->parent != RBTN->nil && y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else 
            {
                if (z == z->parent->right) 
                {
                    z = z->parent;
                    leftRotate(RBTN, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(RBTN, z->parent->parent);
            }
        } 
        else 
        {
            RBTreeNodesElement* y = z->parent->parent->left;
            if (y->parent != RBTN->nil && y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else 
            {
                if (z == z->parent->left) 
                {
                    z = z->parent;
                    rightRotate(RBTN, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(RBTN, z->parent->parent);
            }
        }
    }
    RBTN->root->color = BLACK;
}

void addNode (RBTreeNodes* RBTN, Node* n)
{
    if (!RBTN || !n) return;

    RBTreeNodesElement* new_RBTNE = createRBTreeNodesElement(RBTN, n);
    RBTreeNodesElement* y = RBTN->nil;
    RBTreeNodesElement* x = RBTN->root;
    
    while (x != RBTN->nil) 
    {
        y = x;
        if (strcmp(n->id, x->node->id) < 0) 
        {
            x = x->left;
        } 
        else
        {
            x = x->right;
        }
    }
    
    new_RBTNE->parent = y;
    if (y == RBTN->nil) 
    {
        RBTN->root = new_RBTNE;
    } 
    else if (strcmp(n->id, y->node->id) < 0) 
    {
        y->left = new_RBTNE;
    } 
    else 
    {
        y->right = new_RBTNE;
    }
    
    addFixup(RBTN, new_RBTNE);
    (RBTN->count)++;
}

void transplant(RBTreeNodes* RBTN, RBTreeNodesElement* u, RBTreeNodesElement* v) {
    if (u->parent == RBTN->nil) 
    {
        RBTN->root = v;
    } 
    else if (u == u->parent->left) 
    {
        u->parent->left = v;
    } 
    else 
    {
        u->parent->right = v;
    }
    if (v != RBTN->nil)
    {
        v->parent = u->parent;
    }
    
}

RBTreeNodesElement* minimum(RBTreeNodes* RBTN, RBTreeNodesElement* x) {
    while (x->left != RBTN->nil) {
        x = x->left;
    }
    return x == RBTN->nil ? NULL : x;
}

void deleteFixup(RBTreeNodes* RBTN, RBTreeNodesElement* x) {
    while (x != RBTN->root && x->color == BLACK) 
    {
        if (x == x->parent->left) 
        {
            RBTreeNodesElement* w = x->parent->right;
            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(RBTN, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else 
            {
                if (w->right->color == BLACK) 
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(RBTN, w);
                    w = x->parent->right;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(RBTN, x->parent);
                x = RBTN->root;
            }
        } 
        else 
        {
            RBTreeNodesElement* w = x->parent->left;
            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(RBTN, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else 
            {
                if (w->left->color == BLACK) 
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(RBTN, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(RBTN, x->parent);
                x = RBTN->root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNode(RBTreeNodes* RBTN, RBTreeNodesElement* RBTNE) {
    
    RBTreeNodesElement* y = RBTNE;
    RBTreeNodesElement* x;
    Color y_original_color = y->color;
    
    if (RBTNE->left == RBTN->nil) 
    {
        x = RBTNE->right;
        transplant(RBTN, RBTNE, RBTNE->right);
    } 
    else if (RBTNE->right == RBTN->nil) 
    {
        x = RBTNE->left;
        transplant(RBTN, RBTNE, RBTNE->left);
    } 
    else 
    {
        y = minimum(RBTN, RBTNE->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->parent == RBTNE) 
        {
            x->parent = y;
        } 
        else 
        {
            transplant(RBTN, y, y->right);
            y->right = RBTNE->right;
            if (y->right != RBTN->nil)
            {
                 y->right->parent = y;
            }
            else if (x != RBTN->nil)
            {
                x->parent = y;
            }
        }
        
        transplant(RBTN, RBTNE, y);
        y->left = RBTNE->left;
        y->left->parent = y;
        y->color = RBTNE->color;
    }
    
    if (y_original_color == BLACK && x != RBTN->nil) {
        deleteFixup(RBTN, x);
    }
    
    freeRBTreeNodesElement(RBTNE);
    (RBTN->count)--;
}

void freeRBTreeNodes (RBTreeNodes* RBTN)
{
    if (RBTN->root != RBTN->nil) 
    {
        StackRBTNE* garbage_SRBTNE = createStackRBTNE(RBTN->count);
        pushStackRBTNE(garbage_SRBTNE, RBTN->root);
        while (!isEmptyStackRBTNE(garbage_SRBTNE))
        {
            RBTreeNodesElement* cur_RBTNE = popStackRBTNE(garbage_SRBTNE);
            if (cur_RBTNE->left != RBTN->nil)
            {
                pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->left);
            }
            if (cur_RBTNE->right != RBTN->nil)
            {
                pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->right);
            }
            freeRBTreeNodesElement(cur_RBTNE);
        }
        freeStackRBTNE(garbage_SRBTNE);
    }
    freeRBTreeNodesElement(RBTN->nil);
    
    free(RBTN);
}

void printRBTreeNodes(RBTreeNodes* RBTN, RBTreeNodesElement* RBTNE) 
{
    if (RBTNE == RBTN->nil) return;
    
    printRBTreeNodes(RBTN, RBTNE->left);
    printf("%s ", RBTNE->node->id);
    printRBTreeNodes(RBTN, RBTNE->right);
}

RBTreeNodesElement* findWhiteRBTNE (RBTreeNodes* RBTN)
{
    if (RBTN->root == RBTN->nil) return RBTN->nil;

    StackRBTNE* new_SRBTNE = createStackRBTNE(RBTN->count);
    pushStackRBTNE(new_SRBTNE, RBTN->root);
    while (!isEmptyStackRBTNE(new_SRBTNE))
    {
        RBTreeNodesElement* cur_RBTNE = popStackRBTNE(new_SRBTNE);
        if (cur_RBTNE->node->pre == 0)
        {
            freeStackRBTNE(new_SRBTNE);
            return cur_RBTNE;
        }

        if (cur_RBTNE->right != RBTN->nil)
        {
            pushStackRBTNE(new_SRBTNE, cur_RBTNE->right);
        }
        if (cur_RBTNE->left != RBTN->nil)
        {
            pushStackRBTNE(new_SRBTNE, cur_RBTNE->left);
        }
    }
    freeStackRBTNE(new_SRBTNE);
    return RBTN->nil;
}

/* Генерация стека с PO нумерацией (pre и post используются в контексте их названия) */
StackNodes* getRPO(RBTreeNodes* RBTN, RBTreeNodesElement* start_RBTNE) 
{
    if (start_RBTNE == RBTN->nil) return NULL;

    StackNodes* result = createStackNodes(RBTN->count);
    uint32_t time = 0;

    //Цикл для обработки всех вершин
    while (!isFullStackNodes(result)) 
    {
        StackNodes* inter_SN = createStackNodes(RBTN->count);

        RBTreeNodesElement* cur_start_RBTNE = NULL;
        //uint32_t result_count = 0;
        if (isEmptyStackNodes(result))
        {
            cur_start_RBTNE = start_RBTNE;
        }
        else
        {
            cur_start_RBTNE = findWhiteRBTNE(RBTN);
        }

        pushStackNodes(inter_SN, cur_start_RBTNE->node);

        //Цикл для обработки вершин, до которых есть доступ из текущей
        while (!isEmptyStackNodes(inter_SN)) 
        {
            Node* cur_node = popStackNodes(inter_SN);

            if (cur_node->pre == 0)
            {
                cur_node->pre = ++time;
                pushStackNodes(inter_SN, cur_node);
                for (ListEdgesElement* out_LEE = cur_node->out_edges->tail; out_LEE; out_LEE = out_LEE->prev)
                {
                    Node* post_node = out_LEE->edge->to;

                    if (post_node->pre == 0)
                    {
                        pushStackNodes(inter_SN, post_node);
                    }
                    else if (post_node->post == 0)
                    {
                        printf("Found loop %s->%s\n", cur_node->id, post_node->id);
                    }
                    
                }
            }
            else if (cur_node->post == 0)
            {
                cur_node->post = ++time;
                pushStackNodes(result, cur_node);

            }
        }
        freeStackNodes (inter_SN);
    }

    return result;
}

/* Генерация очереди вершин для вывода в одноимённом алгоритме*/
PriorityQueueNodes* Dijkstra (RBTreeNodes* RBTN, Node* n)
{
    PriorityQueueNodes* result = createPriorityQueueNodes(RBTN->count); 
    
    PriorityQueueNodes* inter_PQN = createPriorityQueueNodes(RBTN->count); //Приоритетная очередь непосредственно для реализации самого алгоритма
    uint32_t time = 1;
    n->distance = 0;
    n->pre = time;
    enPriorityQueueNodes(inter_PQN, n);
    
    while (!isEmptyPriorityQueueNodes(inter_PQN))
    {
        ++time;
        Node* cur_node = dePriorityQueueNodes(inter_PQN);
        if (cur_node->index < 1) 
        {
            enPriorityQueueNodes(result, cur_node);
        }

        cur_node->index = 1;

        for (ListEdgesElement* cur_LEE = cur_node->out_edges->head; cur_LEE; cur_LEE = cur_LEE->next)
        {   
            Node* next_node = cur_LEE->edge->to;

            uint32_t new_dist = cur_LEE->edge->value + cur_node->distance;
            if (new_dist < next_node->distance)
            {
                next_node->distance = new_dist;
                next_node->pre = time;
                enPriorityQueueNodes(inter_PQN, next_node);
            }
        }
    }
    freePriorityQueueNodes(inter_PQN);
    return result;
}

void printNodes (RBTreeNodes* RBTN)
{
    if (RBTN->root == RBTN->nil) return;

    printRBTreeNodes(RBTN, RBTN->root);
    printf("\n");
}