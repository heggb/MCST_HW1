#define _GNU_SOURCE

#include "pch.h"


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

    while (read_line (&line, stdin) != SIZE_MAX)
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
            end_oper = (substr_ptr - input) + strlen(variant_set[i]);
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

    if (read == SIZE_MAX) {
        return -1;
    }

    if (read > 0 && (*lineptr)[read - 1] == '\n') {
        (*lineptr)[read - 1] = '\0';
        --read;
    }

    return read;
}


/* Функции для Node */

/* Функции для Edge */

/* Функции для RBTreeNodesElement */

/* Функции для RBTreeNodes */

/* Функции для ListEdgesElement */

/* Функции для ListEdges */

/* Функции для StackNodes */

/* Функции для StackRBTNE */

/* Функции для QueueNodes */

/* Функции для PriorotyQueueNodes */

/* Функции для Graph */

