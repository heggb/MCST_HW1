#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph Graph; 

#include <inttypes.h>
#include "RBTreeNodes.h"
#include "ListEdges.h"

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

#endif