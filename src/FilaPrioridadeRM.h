#include "Nodos.h"

typedef struct PriorityQueueRM
{
    int tam;
    Node *top, *back, *mRef;
} PriorityQueueRM;

int insert(PriorityQueueRM *pq, Data *inf);
PriorityQueueRM* construct();
void destroy(PriorityQueueRM **pq);
Data* top(PriorityQueueRM *pq);
Data* back(PriorityQueueRM *pq);
int pop_top(PriorityQueueRM *pq);
int pop_back(PriorityQueueRM *pq);
