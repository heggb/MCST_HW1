#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>


typedef struct Node Node; 
typedef struct Edge Edge;
typedef struct RBTreeNodesElement RBTreeNodesElement; //Элемент красно-чёрного дерева, в котором хранятся узлы 
typedef struct RBTreeNodes RBTreeNodes;
typedef struct ListEdgesElement ListEdgesElement; //Элемент списка, в котором хранятся узлы
typedef struct ListEdges ListEdges; 
typedef struct StackRBTNE StackRBTNE; //Стек, в котором хранятся элементы красно-чёрного дерева
typedef struct StackNodes StackNodes; 
typedef struct QueueNodes QueueNodes; 
typedef struct PriorityQueueNodesElement PriorityQueueNodesElement; //Элемент приоритетной очереди, в которой хранятся узлы
typedef struct PriorityQueueNodes PriorityQueueNodes;
typedef struct Graph Graph; 
typedef enum {BLACK, RED} Color; //Цвета для окрашивания в дереве


struct Node
{
    uint32_t count_ptr; //Счётчик для структур данных, в которых указатель на вершину планируется находится дольше одной функции
    
    const char* id;
    ListEdges *in_edges, *out_edges; //Массивы входящих и исходящих ребёр, соответсвенно
    Node* parent_node; 
    uint32_t index, pre, post; //Доп. параметры, которые используются при различных обходах
    uint32_t distance; 
};

Node* createNode (const char* name);
void freeNode (Node* n);


struct Edge
{
    uint32_t count_ptr; //Счётчик для структур данных, в которых указатель на узел планируется находится дольше одной функции

    uint32_t value, reverse_value; //Прямое и обратное значение величины ребра для нахождения макс. потока
    Node *from, *to;
};

Edge* createEdge (Node* node_from, Node* node_to, uint32_t value);


struct RBTreeNodesElement
{
    Node* node;
    Color color;
    RBTreeNodesElement *parent, *left, *right;
};

RBTreeNodesElement* createRBTreeNodesElement (RBTreeNodes* RBTN, Node* n);
void freeRBTreeNodesElement(RBTreeNodesElement* RBTNE);


struct RBTreeNodes 
{
    uint32_t count;
    RBTreeNodesElement *root, *nil;
};

RBTreeNodes* createRBTreeNodes();
void addNode(RBTreeNodes* RBTN, Node* n);
//RBTreeNodesElement* findRBTreeNodesElement (RBTreeNodes* RBTN, const char* name_node);
Node* findNode (RBTreeNodes* RBTN, const char* name_node);
void deleteNode (RBTreeNodes* RBTN, RBTreeNodesElement* RBTNE);
void printNodes (RBTreeNodes* RBTN);
void freeRBTreeNodes (RBTreeNodes* RBTN);

struct ListEdgesElement
{
    Edge* edge;
    ListEdgesElement *prev, *next;
};

ListEdgesElement* createListEdgesElement (Edge* e);
void freeListEdgesElement(ListEdgesElement* LEE);


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


struct StackNodes
{
    Node** nodes;
    uint32_t capacity;
    int64_t top;
};

StackNodes* createStackNodes (uint32_t capacity);
void pushStackNodes (StackNodes* SN, Node* n);
Node* popStackNodes (StackNodes* SN);
bool isEmptyStackNodes (StackNodes* SN);
bool isFullStackNodes (StackNodes* SN);
void freeStackNodes (StackNodes* SN);


struct QueueNodes
{
    Node** nodes;
    uint32_t capacity, count;
    int64_t front, top;
};

QueueNodes* createQueueNodes (uint32_t capacity);
bool isEmptyQueueNodes (QueueNodes* QN);
bool isFullQueueNodes (QueueNodes* QN);
void enQueueNodes (QueueNodes* QN, Node* n);
Node* deQueueNodes (QueueNodes* QN);
void freeQueueNodes (QueueNodes* QN);

struct PriorityQueueNodes
{
    Node** heap;
    uint32_t capacity, size;
};

PriorityQueueNodes* createPriorityQueueNodes (uint32_t capacity);
bool isEmptyPriorityQueueNodes (PriorityQueueNodes* PQN);
bool isFullPrioorityQueueNodes (PriorityQueueNodes* PQN);
void enPriorityQueueNodes (PriorityQueueNodes* PQN, Node* n);
Node* dePriorityQueueNodes (PriorityQueueNodes* PQN);
void freePriorityQueueNodes (PriorityQueueNodes* PQN);


struct Graph
{
    RBTreeNodes* nodes;
    ListEdges* edges;
};

Graph* createGraph();
void addNamedNode (Graph* G, const char* name_node);
void addWeightedEdge (Graph* G, const char* name_node_from, const char* name_node_to, uint32_t value);
void deleteNamedNode (Graph* G, const char* name_node);
void deleteWeightedEdge (Graph* G, const char* name_node_from, const char* name_node_to);
void printRPO (Graph* G, const char* start_node);
void printDijkstra (Graph* G, const char* start_node);
void printMaxFlowDinic (Graph* G, const char* source_name, const char* sink_name);
void printTarjan (Graph* G, const char* source_name);
void printGraph(Graph* G);
void freeGrapgh (Graph* G);


typedef enum {REMOVE_NODE, REMOVE_EDGE, NODE, EDGE, RPO_NUMBERING, DIJKSTRA, MAX_FLOW, TARJAN, INVALID_OPERATION} Operation; 

char** getArgs (char* str_args, uint8_t count_args); //Функция для получения массива аргументов введённой комманды
Operation parser (Graph* G, char* input, const char** variant_set, size_t size); 
size_t read_line(char** lineptr, FILE* file); //Функция для чтения введённых строк произвольной длины

int main()
{
    const char* variant_set[] = {
        "REMOVE NODE ",
        "REMOVE EDGE ",
        "NODE ",
        "EDGE ",
        "RPO_NUMBERING ",
        "DIJKSTRA ",
        "MAX FLOW ",
        "TARJAN "
    };

    size_t size = sizeof(variant_set) / sizeof(variant_set[0]);
    
    Graph* G = createGraph();

    char* line = NULL;

    while (read_line (&line, stdin) != -1)
    {
        Operation oper = parser (G, line, variant_set, size);
        //printGraph(G);
        free(line);
        line = NULL;
        if (oper == INVALID_OPERATION) 
        {
            break;
        }
    }
    
    freeGrapgh(G);

    return 0;
}




char** getArgs (char* str_args, uint8_t count_args)
{
    char** args = (char**)malloc(count_args * sizeof(const char*));
    char* token = strtok (str_args, " ");
    for (uint8_t i = 0; i < count_args; i++)
    {
        args[i] = token ? token : "";
        token = strtok(NULL, " ");
    }
    return args;
}

Operation parser (Graph* G, char* input, const char** variant_set, size_t size)
{
    char* substr_ptr = NULL; //Указатель на первое вхождение команды в введёной строке
    Operation cur_oper;
    long end_oper = 0; //Смещение, с которого нужно искать аргументы
    bool check_find = false;
    for (size_t i = 0; i < size; i++)
    {
        substr_ptr = strstr(input, variant_set[i]);
        check_find = substr_ptr && substr_ptr == input;
        if (check_find) 
        {
            //end_oper = (substr_ptr - input) + strlen(variant_set[i]);
            cur_oper = (Operation)i;
            break;
        }
    }
    if (!check_find) return INVALID_OPERATION;

    char** args = NULL;
    uint8_t count_args = 0;

    switch (cur_oper)
    {
    case NODE:
        count_args = 1;    
        args = getArgs(input + end_oper, count_args);
        addNamedNode(G, args[0]);
        break;

    case EDGE:
        count_args = 3;    
        args = getArgs(input + end_oper, count_args);
        addWeightedEdge(G, args[0], args[1], (uint32_t)strtol(args[2], NULL, 10));
        break;

    case REMOVE_NODE:
        count_args = 1;    
        args = getArgs(input + end_oper, count_args);
        deleteNamedNode(G, args[0]);
        break;

    case REMOVE_EDGE:
        count_args = 2;    
        args = getArgs(input + end_oper, count_args);
        deleteWeightedEdge(G, args[0], args[1]);
        break;

    case RPO_NUMBERING:
        count_args = 1;
        args = getArgs(input + end_oper, count_args);
        printRPO(G, args[0]);
        break;

    case DIJKSTRA:
        count_args = 1;    
        args = getArgs(input + end_oper, count_args);
        printDijkstra(G, args[0]);
        break;

    case MAX_FLOW:
        count_args = 2;    
        args = getArgs(input + end_oper, count_args);
        printMaxFlowDinic(G, args[0], args[1]);
        break;

    case TARJAN:
        count_args = 1;    
        args = getArgs(input + end_oper, count_args);
        printTarjan(G, args[0]);
        break;

    default:
        break;
    }

    free(args);
    return cur_oper;

}

size_t read_line(char** lineptr, FILE* file) {
    size_t len = 0;
    size_t read = getline(lineptr, &len, file);

    if (read == -1) {
        return -1;
    }

    if (read > 0 && (*lineptr)[read - 1] == '\n') {
        (*lineptr)[read - 1] = '\0';
        --read;
    }

    return read;
}


/* Функции для Node */

Node* createNode (const char* name)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = strdup(name);
    new_node->in_edges = createListEdges();
    new_node->out_edges = createListEdges();
    //new_node->state = WHITE_S;
    new_node->count_ptr = 0;
    new_node->index = new_node->pre = new_node->post = 0;
    new_node->distance = UINT32_MAX;
    new_node->parent_node = NULL;
    return new_node;
}

void freeNode (Node* n)
{
    free((char*)(n->id));
    freeListEdges(n->in_edges);
    freeListEdges(n->out_edges);
    free(n);
}

/* Функции для Edge */
Edge* createEdge (Node* node_from, Node* node_to, uint32_t value)
{
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->value = value;
    new_edge->from = node_from;
    new_edge->to = node_to;
    new_edge->count_ptr = 0;
    new_edge->reverse_value = 0;
    return new_edge;
}


/* Функции для RBTreeNodesElement */

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


/* Функции для RBTreeNodes */

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


/* Функции для ListEdgesElement */

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

/* Функции для ListEdges */

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


/* Функции для StackNodes */

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


/* Функции для StackRBTNE */

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


/* Функции для QueueNodes */

QueueNodes* createQueueNodes (uint32_t capacity)
{
    QueueNodes* new_QN = (QueueNodes*)malloc(sizeof(QueueNodes));
    new_QN->nodes = (Node**)malloc(capacity * sizeof(Node*));
    new_QN->capacity = capacity;
    new_QN->front = 0;
    new_QN->top = 0;
    new_QN->count = 0;
    
    return new_QN;
}

bool isEmptyQueueNodes (QueueNodes* QN)
{
    return QN->count == 0;
}

bool isFullQueueNodes (QueueNodes* QN)
{
    return QN->count == QN->capacity;
}

void enQueueNodes (QueueNodes* QN, Node* n)
{
    QN->nodes[QN->top] = n; 
    QN->top = (QN->top + 1) % QN->capacity;
    QN->count++;
    
}
Node* deQueueNodes (QueueNodes* QN)
{
    Node* node = QN->nodes[QN->front];
    QN->front = (QN->front + 1) % QN->capacity;
    QN->count--;
    return node;
}

void freeQueueNodes (QueueNodes* QN)
{
    free(QN->nodes);
    free(QN);
}


/* Функции для PriorotyQueueNodes */

void swap (Node** n1, Node** n2)
{
    Node* temp_node = *n1;
    *n1 = *n2;
    *n2 = temp_node;
}

void heapifyUp(PriorityQueueNodes* PQN, uint32_t index) {
    while (index > 0) {
        uint32_t parent = (index - 1) / 2;
        if (PQN->heap[index]->distance >= PQN->heap[parent]->distance) {
            break;
        }
        swap(&(PQN->heap[index]), &(PQN->heap[parent]));
        index = parent;
    }
}

void heapifyDown(PriorityQueueNodes* PQN, uint32_t index) {
    while (true)
    {
        uint32_t smallest = index;
        uint32_t left = 2 * index + 1;
        uint32_t right = 2 * index + 2;

        if (left < PQN->size && PQN->heap[left]->distance < PQN->heap[smallest]->distance)
        {
            smallest = left;
        }

        if (right < PQN->size && PQN->heap[right]->distance < PQN->heap[smallest]->distance)
        {
            smallest = right;
        }

        if (smallest == index) 
        {
            break;    
        }

        swap(&PQN->heap[index], &PQN->heap[smallest]);
        index = smallest;
    }
}

PriorityQueueNodes* createPriorityQueueNodes (uint32_t capacity)
{
    PriorityQueueNodes* PQN = (PriorityQueueNodes*)malloc(sizeof(PriorityQueueNodes));

    PQN->heap = (Node**)malloc(capacity* sizeof(Node*));
    PQN->capacity = capacity;
    PQN->size = 0;
    return PQN;

}

bool isEmptyPriorityQueueNodes (PriorityQueueNodes* PQN)
{
    return PQN->size < 1;
}

bool isFullPrioorityQueueNodes (PriorityQueueNodes* PQN)
{
    return PQN->size == PQN->capacity;
}

void enPriorityQueueNodes (PriorityQueueNodes* PQN, Node* n)
{
    PQN->heap[PQN->size] = n;
    heapifyUp(PQN, PQN->size);
    PQN->size++;
}

Node* dePriorityQueueNodes (PriorityQueueNodes* PQN)
{
    Node* min_node = PQN->heap[0];
    PQN->heap[0] = PQN->heap[--PQN->size];
    heapifyDown(PQN, 0);
    return min_node;
}

void freePriorityQueueNodes (PriorityQueueNodes* PQN)
{
    free(PQN->heap);
    free(PQN);
}


/* Функции для Graph */

Graph* createGraph()
{
    Graph* new_G = (Graph*)malloc(sizeof(Graph));
    new_G->nodes = createRBTreeNodes();
    new_G->edges = createListEdges();
    return new_G;
}
void addNamedNode (Graph* G, const char* name_node)
{
    if (findNode(G->nodes, name_node)) return;
    addNode(G->nodes, createNode(name_node));
}
void addWeightedEdge (Graph* G, const char* name_node_from, const char* name_node_to, uint32_t value)
{
    Node* start_node = findNode(G->nodes, name_node_from);
    Node* end_node = findNode(G->nodes, name_node_to);

    if (!start_node && !end_node) 
    {
        printf("Unknown nodes %s %s\n", name_node_from, name_node_to);
        return;
    }
    else if (!start_node)
    {
        printf("Unknown node %s\n", name_node_from);
        return;
    }
    else if (!end_node)
    {
        printf("Unknown node %s\n", name_node_to);
        return;
    }
    if (findEdge(start_node, end_node) || findEdge(end_node, start_node)) return;

    Edge* new_edge = createEdge(start_node, end_node, value);
    addEdge(G->edges, new_edge);
    addEdge(new_edge->from->out_edges, new_edge);
    addEdge(new_edge->to->in_edges, new_edge);
}
void deleteNamedNode (Graph* G, const char* name_node)
{
    RBTreeNodesElement* del_RBTNE = findRBTreeNodesElement(G->nodes, name_node);
    if (del_RBTNE == G->nodes->nil)
    {
        printf("Unknown node %s\n", name_node);
        return;
    }
    //Удаление в следующих 2-х for нужна для очистки инцидентных рёбер их из списков входящих/исходящих рёбер других вершин 
    for (ListEdgesElement* cur_LEE = del_RBTNE->node->in_edges->head; cur_LEE;)
    {
        ListEdgesElement* next_LEE = cur_LEE->next;

        Node* cur_node_from = cur_LEE->edge->from;

        deleteEdge (del_RBTNE->node->in_edges, cur_LEE);
        deleteEdge (cur_node_from->out_edges, findListEdgesElement(cur_node_from->out_edges, cur_node_from, del_RBTNE->node));

        cur_LEE = next_LEE;
    }

    for (ListEdgesElement* cur_LEE = del_RBTNE->node->out_edges->head; cur_LEE;)
    {
        ListEdgesElement* next_LEE = cur_LEE->next;

        Node* cur_node_to = cur_LEE->edge->to;

        deleteEdge (del_RBTNE->node->out_edges, cur_LEE);
        deleteEdge (cur_node_to->in_edges, findListEdgesElement(cur_node_to->in_edges, del_RBTNE->node, cur_node_to));
        
        cur_LEE = next_LEE;
    }

    //Очистка из списка рёбер графа
    for (ListEdgesElement* cur_LEE = G->edges->head; cur_LEE;)
    {
        ListEdgesElement* next_LEE = cur_LEE->next;
        if (cur_LEE->edge->from == del_RBTNE->node || cur_LEE->edge->to == del_RBTNE->node)
        {
            deleteEdge(G->edges, cur_LEE);
        }
        cur_LEE = next_LEE;
    }
    deleteNode(G->nodes, del_RBTNE);
}

void deleteWeightedEdge (Graph* G, const char* name_node_from, const char* name_node_to)
{
    RBTreeNodesElement* start_RBTNE = findRBTreeNodesElement(G->nodes, name_node_from);
    RBTreeNodesElement* end_RBTNE = findRBTreeNodesElement(G->nodes, name_node_to);
    if (start_RBTNE == G->nodes->nil && end_RBTNE == G->nodes->nil) 
    {
        printf("Unknown nodes %s %s\n", name_node_from, name_node_to);
        return;
    }
    else if (start_RBTNE == G->nodes->nil)
    {
        printf("Unknown node %s\n", name_node_from);
        return;
    }
    else if (end_RBTNE == G->nodes->nil)
    {
        printf("Unknown node %s\n", name_node_to);
        return;
    }

    Node* node_from = start_RBTNE->node;
    Node* node_to = end_RBTNE->node;
    
    //Очистка заданного ребра из списков рёбер графа и вершин, которые соединяет  
    deleteEdge(node_from->out_edges, findListEdgesElement(node_from->out_edges, node_from, node_to));
    deleteEdge(node_to->in_edges, findListEdgesElement(node_to->in_edges, node_from, node_to));
    deleteEdge(G->edges, findListEdgesElement(G->edges, node_from, node_to));
}

void printRPO (Graph* G, const char* start_node)
{
    RBTreeNodesElement* start_RBTNE = findRBTreeNodesElement(G->nodes, start_node);

    if (start_RBTNE == G->nodes->nil) return;

    StackNodes* RPO_SN = getRPO(G->nodes, start_RBTNE);
    
    //Возвращение к значениям по умолчанию параметров вершин, используемых в алгоритме
    while (!isEmptyStackNodes(RPO_SN))
    {
        Node* cur_node = popStackNodes(RPO_SN);
        cur_node->post = cur_node->pre = 0;
        printf("%s ", cur_node->id);
    }
    freeStackNodes(RPO_SN);
    
    printf("\n");
}

bool DinicBFS (Graph* G, Node* source_node, Node* sink_node)
{
    //index отвечает за уникальную динамическую индексацию
    //pre отвечает за нумерацию уровней
    QueueNodes* QN = createQueueNodes(G->nodes->count);
    source_node->pre = 1;
    source_node->post = 1;
    uint32_t time = 0;
    enQueueNodes(QN, source_node);

    while (!isEmptyQueueNodes(QN))
    {
        Node* cur_node = deQueueNodes(QN);
        cur_node->index = time;
        ++time;

        for (ListEdgesElement* cur_LEE = cur_node->out_edges->head; cur_LEE; cur_LEE = cur_LEE->next)
        {   
            Edge* cur_edge = cur_LEE->edge;

            if (cur_edge->value > 0 && cur_edge->to->pre == 0)
            {
                cur_edge->to->pre = cur_node->pre + 1;
                enQueueNodes(QN, cur_edge->to);
            }
        }
    }
    freeQueueNodes(QN);
    return sink_node->pre != 0;
}

uint32_t DinicDFS (Graph* G, Node* source_node, Node* sink_node)
{
    //index отвечает за уникальную динамическую индексацию
    //pre отвечает за нумерацию уровней
    //post отвечает за состояние пройденности вершины (0 - не посещена, 1 - посещена)
    StackNodes* SN = createStackNodes(G->nodes->count);
    pushStackNodes (SN, source_node);
    Edge** parentEdges = (Edge**)malloc((G->edges->count + 1) * sizeof(Edge*));
    for (uint32_t i = 0; i < G->edges->count; i++)
    {
        parentEdges[i] = NULL;
    }

    while (!isEmptyStackNodes(SN))
    {   
        Node* cur_node = popStackNodes(SN);
        

        if (cur_node == sink_node)
        {
            uint32_t path_flow = UINT32_MAX;
            for (Node* end_node = sink_node; end_node != source_node; end_node = parentEdges[end_node->index]->from)
            {
                path_flow = path_flow < parentEdges[end_node->index]->value ? path_flow : parentEdges[end_node->index]->value;
            }
            
            for (Node* end_node = sink_node; end_node != source_node; end_node = parentEdges[end_node->index]->from)
            {
                Edge* parent_edge = parentEdges[end_node->index];
                parent_edge->value -= path_flow;
                parent_edge->reverse_value += path_flow;
            } 

            freeStackNodes(SN);
            free(parentEdges);
            return path_flow;
        }

        for (ListEdgesElement* cur_LEE = cur_node->out_edges->tail; cur_LEE; cur_LEE = cur_LEE->prev)
        {
            Edge* cur_edge = cur_LEE->edge;
            if (cur_edge->value > 0 && cur_edge->to->pre == cur_node->pre + 1 && cur_edge->to->post == 0)
            {
                parentEdges[cur_edge->to->index] = cur_edge;
                cur_edge->to->post = 1;
                pushStackNodes(SN, cur_edge->to);
            }
        }
    }

    freeStackNodes(SN);
    free(parentEdges);

    return 0;
}

void printMaxFlowDinic (Graph* G, const char* source_name, const char* sink_name)
{
    Node* source_node = findNode(G->nodes, source_name);
    Node* sink_node = findNode(G->nodes, sink_name);

    if (!source_node || !sink_node || source_node == sink_node) 
    {
        printf("0\n");
        return;
    }

    source_node->pre = source_node->post = 1;

    uint32_t max_flow = 0;

    StackRBTNE* garbage_SRBTNE = createStackRBTNE(G->nodes->count);

    //Проверка на существующие связи между стоком и и стоком
    while (DinicBFS(G, source_node, sink_node))
    {
        uint32_t flow = DinicDFS (G, source_node, sink_node);
        while (flow > 0)
        {
            max_flow += flow;
            flow = DinicDFS (G, source_node, sink_node);
            pushStackRBTNE(garbage_SRBTNE, G->nodes->root);
            //Обнуление пройденности вершины
            while (!isEmptyStackRBTNE(garbage_SRBTNE))
            {
                RBTreeNodesElement* cur_RBTNE = popStackRBTNE(garbage_SRBTNE);
                cur_RBTNE->node->post = 0;
                if (cur_RBTNE->left != G->nodes->nil) 
                {
                    pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->left);
                }
                if (cur_RBTNE->right != G->nodes->nil) 
                {
                    pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->right);
                }
            }
        }

        //Возвращение к значениям по умолчанию параметров вершин, используемых в алгоритме
        pushStackRBTNE(garbage_SRBTNE, G->nodes->root);
        while (!isEmptyStackRBTNE(garbage_SRBTNE))
        {
            RBTreeNodesElement* cur_RBTNE = popStackRBTNE(garbage_SRBTNE);
            cur_RBTNE->node->post = 0;
            cur_RBTNE->node->pre = 0;
            cur_RBTNE->node->index = 0;
            if (cur_RBTNE->left != G->nodes->nil) 
            {
                pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->left);
            }
            if (cur_RBTNE->right != G->nodes->nil) 
            {
                pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->right);
            }
        }
    }
    //Возвращение к значениям по умолчанию параметров узлов, используемых в алгоритме
    for (ListEdgesElement* cur_LEE = G->edges->head; cur_LEE; cur_LEE = cur_LEE->next)
    {
        if (cur_LEE->edge->reverse_value) 
        {
            cur_LEE->edge->value += cur_LEE->edge->reverse_value;
            cur_LEE->edge->reverse_value = 0;
        }
    }
    freeStackRBTNE(garbage_SRBTNE);

    printf("%"PRIu32"\n", max_flow);
}

void printDijkstra (Graph* G, const char* start_node)
{
    // pre отвечает за посещённость вершины (0 - не посещена, 1 - посещена)
    Node* start_n = findNode(G->nodes, start_node);

    if (!start_n) return;

    PriorityQueueNodes* Dijkstra_PQN = Dijkstra (G->nodes, start_n);

    // Поиск вершин, до которого нет путей из стартовой вершины
    uint32_t white_QN_size = G->nodes->count - Dijkstra_PQN->size; 
    QueueNodes* white_QN = NULL;
    if (white_QN_size)
    {
        white_QN = createQueueNodes(white_QN_size);
        while (!isFullQueueNodes(white_QN)) 
        {
            RBTreeNodesElement* white_RBTNE = findWhiteRBTNE(G->nodes);
            white_RBTNE->node->pre = 1; 
            enQueueNodes(white_QN, white_RBTNE->node);
        }
    }

    Node* cur_node = dePriorityQueueNodes(Dijkstra_PQN);
    cur_node->pre = 0;
    cur_node->distance = INT32_MAX;

    //Вывод результатов и возвращение к значениям по умолчанию параметров вершин, используемых в алгоритме
    while (!isEmptyPriorityQueueNodes(Dijkstra_PQN))
    {
        cur_node = dePriorityQueueNodes(Dijkstra_PQN);
        
        printf("%s: %"PRIu32" \n", cur_node->id, cur_node->distance);
        cur_node->pre = 0;
        cur_node->distance = INT32_MAX;
        cur_node->index = 0;
    }

    while (white_QN_size && !isEmptyQueueNodes(white_QN))
    {
        cur_node = deQueueNodes(white_QN);
        cur_node->pre = 0;
        printf("%s: %"PRIu32" \n", cur_node->id, cur_node->distance);
    }

    freePriorityQueueNodes(Dijkstra_PQN);
    if (white_QN_size)
    {
        freeQueueNodes (white_QN);
    }
}

/* Вывод КСС, достижимых из заданной вершины */
void printSCC (RBTreeNodes* RBTN, Node* n, uint32_t* time)
{
    //index отвечает за состояние пройденности вершины (0 - не посещена, 1 - посещена) 
    //pre отвечает за уникальную динамическую индексацию
    //post отвечает за индекс ближайшую безопасную для отката вершину 
    
    StackNodes* call_SN = createStackNodes(RBTN->count); //стек для поиска в глубину
    StackNodes* inter_SN = createStackNodes(RBTN->count); //стек для хранения КСС
    pushStackNodes(call_SN, n);

    while (!isEmptyStackNodes(call_SN))
    {
        Node* cur_node = popStackNodes(call_SN);

        if (cur_node->post == 0)
        {
            cur_node->post = cur_node->pre = ++(*time);
            cur_node->index = 1;
            pushStackNodes(inter_SN, cur_node);
        }

        bool all_visited = true;
        for (ListEdgesElement* cur_LEE = cur_node->out_edges->tail; cur_LEE; cur_LEE = cur_LEE->prev)
        {
            Node* next_node = cur_LEE->edge->to;
            if (next_node->post == 0)
            {
                next_node->parent_node = cur_node;
                pushStackNodes(call_SN, cur_node);
                pushStackNodes(call_SN, next_node);
                all_visited = false;
            }
            else if (next_node->index)
            {
                if (next_node->pre < cur_node->pre)
                {
                    cur_node->pre = next_node->pre;
                }
            }
        }

        if (!all_visited)
            continue;

        if (cur_node->parent_node && cur_node->pre < cur_node->parent_node->pre)
        {
            cur_node->parent_node->pre = cur_node->pre;
        }

        if (inter_SN->top > 0 && cur_node->index && cur_node->post == cur_node->pre)
        {
            Node* node_SCC = NULL;
            bool flag_print = (cur_node != inter_SN->nodes[inter_SN->top]);
            do 
            {
                node_SCC = popStackNodes(inter_SN);
                node_SCC->index = 0;
                if (flag_print)
                {
                    printf("%s ", node_SCC->id);
                }
                 
            } while (node_SCC != cur_node && !isEmptyStackNodes(inter_SN));
            
            if (flag_print) 
            {
                printf("\n");
            }
        }
    }

    freeStackNodes(inter_SN);
    freeStackNodes(call_SN);
}

void printTarjan (Graph* G, const char* source_name)
{
    RBTreeNodesElement* source_RBTNE = findRBTreeNodesElement(G->nodes, source_name);

    if (source_RBTNE == G->nodes->nil) return;
    
    uint32_t time = 0;

    while (source_RBTNE != G->nodes->nil)
    {
        printSCC (G->nodes, source_RBTNE->node, &time);
        source_RBTNE = findWhiteRBTNE (G->nodes);
    }

    //Возвращение к значениям по умолчанию параметров вершин, используемых в алгоритме
    StackRBTNE* garbage_SRBTNE = createStackRBTNE(G->nodes->count);
    pushStackRBTNE(garbage_SRBTNE, G->nodes->root);
    while (!isEmptyStackRBTNE(garbage_SRBTNE))
    {
        RBTreeNodesElement* cur_RBTNE = popStackRBTNE(garbage_SRBTNE);
        cur_RBTNE->node->index = 0;
        cur_RBTNE->node->pre = 0;
        cur_RBTNE->node->post = 0;
        cur_RBTNE->node->parent_node = NULL;
        if (cur_RBTNE->left != G->nodes->nil) 
        {
            pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->left);
        }
        if (cur_RBTNE->right != G->nodes->nil)
        {
            pushStackRBTNE(garbage_SRBTNE, cur_RBTNE->right);
        }
    }
    freeStackRBTNE (garbage_SRBTNE);
}

void printGraph(Graph* G)
{
    printNodes(G->nodes);
    printEdges(G->edges);
}

void freeGrapgh (Graph* G)
{
    freeRBTreeNodes(G->nodes);
    freeListEdges(G->edges);
    free(G);
}
