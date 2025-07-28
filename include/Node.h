#ifndef NODE_H
#define NODE_H

#define _GNU_SOURCE

#include <stdint.h>
#include <stdlib.h>
#include <string.h> 

typedef struct Node Node;
typedef struct ListEdges ListEdges;

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

#endif