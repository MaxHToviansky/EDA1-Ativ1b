#include "FilaPrioridadeSemRM.h"
#include <stdlib.h>

PriorityQueue *construct(int tam){
    PriorityQueue *pq = malloc(tam * sizeof(PriorityQueue));
    if(pq==NULL)
        return pq;
    pq->back = NULL;
    pq->top = NULL;
    pq->tam = tam;
    return pq;
}

int comp(Data *a, Data *b){
    if(a->rank > b->rank) // inf > s->info, return 1
        return 1;
    if(a->rank < b->rank) // inf < s->info, return -1
        return -1;
    return 0; // s->info == inf, return 0
}

int insert(PriorityQueue *pq, Data *inf){
    if(pq==NULL || inf==NULL)
        return 1;
    
    Node *s = pq->back;
    Node *ins = createNode();
    ins->info = inf;

    if(!pq->tam){
        pq->top = ins;
        pq->back = ins;
        return 0;
    }    

    while(s!= NULL){
        int now = comp(inf,s->info);  // a->rank = s->info, b->rank = inf
        
        if(now != 1){
            ins->back = s->back;
            ins->front = s;
            s->back = ins;
            if(pq->back == s)
                pq->back = ins;
            break;
        }
        
        s = s->front;   
    } 

    if(ins->back==NULL && ins->front==NULL){
        ins->back = pq->top; // cauda = topo
        pq->top->front = ins; // frente da cauda = ins
        pq->top = ins; // ins = novo topo;
    }
    
    return 0;
}
