#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Node Node;
typedef struct Edge Edge;

struct Edge
{
    uint32_t count_ptr; //Счётчик для структур данных, в которых указатель на узел планируется находится дольше одной функции

    uint32_t value, reverse_value; //Прямое и обратное значение величины ребра для нахождения макс. потока
    Node *from, *to;
};

Edge* createEdge (Node* node_from, Node* node_to, uint32_t value);

#endif