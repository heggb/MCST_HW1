#include "Graph.h"
#include "StackNodes.h"
#include "QueueNodes.h"
#include "StackRBTNE.h"
#include "PriorityQueueNodes.h"

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