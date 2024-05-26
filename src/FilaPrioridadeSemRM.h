#include "Nodos.h"

typedef struct PriorityQueue
{
    int tam;
    Node *top, *back;
} PriorityQueue;

int insert(PriorityQueue *pq, Data *inf);
PriorityQueue* construct();
void destroy(PriorityQueue **pq);
Data* top(PriorityQueue *pq);
Data* back(PriorityQueue *pq);
int pop_top(PriorityQueue *pq);
int pop_back(PriorityQueue *pq);
