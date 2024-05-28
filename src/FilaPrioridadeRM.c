#include "FilaPrioridadeRM.h"


/*************** CRIA ***************/
struct descFRM * criaRM(int tamInfo)
{   	
    struct descFRM *desc = (struct descFRM*) malloc(sizeof(struct descFRM));
    if(desc != NULL) {
        desc->cauda = NULL;
        desc->refMov = NULL;
        desc->frente = NULL;
		desc->tamInfo= tamInfo;
    }
    return desc;
}

/*************** INSERE A PARTIR DA FRENTE ***************/
int insereRM(info *pInfo, struct descFRM *p)
{ 
	int result, mediaIt = 0;
  	struct noFila *novoNoFila=NULL, *visitado=NULL;
  	if ((novoNoFila = (struct noFila *) malloc(sizeof(struct noFila))) != NULL)
    { 
        memcpy(&(novoNoFila->dados),pInfo, p->tamInfo);
        if(p->frente == NULL && p->cauda == NULL) /*fila vazia*/
        {  
            novoNoFila->atras = novoNoFila->defronte = NULL;
            p->frente = p->cauda = novoNoFila;     
        }
        else
        { 
            if(novoNoFila->dados.rank < p->cauda->dados.rank) /*novo elemento � o de menor prior rank */
            { 	
                novoNoFila->atras=NULL;
                novoNoFila->defronte=p->cauda;
                p->cauda->atras=novoNoFila;
                p->cauda=novoNoFila;
                p->refMov = novoNoFila;
                    
            }
            else if(novoNoFila->dados.rank > p->frente->dados.rank){
                novoNoFila->defronte = NULL;
                novoNoFila->atras = p->frente;
                p->frente->defronte = novoNoFila;
                p->frente = novoNoFila;
                p->refMov = novoNoFila;
            } else{
                if(novoNoFila->dados.rank <= p->refMov->dados.rank)
                    if(abs(novoNoFila->dados.rank - p->cauda->dados.rank) < (abs(novoNoFila->dados.rank - p->refMov->dados.rank)))
                        p->refMov = buscaPelaEsquerda(p,novoNoFila,p->cauda, &mediaIt);
                    else
                        p->refMov = buscaPelaDireita(p,novoNoFila,p->refMov, &mediaIt);
                else
                    if(abs(novoNoFila->dados.rank - p->refMov->dados.rank) < abs(novoNoFila->dados.rank - p->frente->dados.rank))
                        p->refMov = buscaPelaEsquerda(p,novoNoFila,p->refMov, &mediaIt);
                    else
                        p->refMov = buscaPelaDireita(p,novoNoFila,p->frente, &mediaIt);       
            }
        }
        return mediaIt;
    }
    
	return FRACASSO;

}


/*************** REMOVE DA FRENTE ***************/
int remove_RM(info *reg, struct descFRM  *p)
{
	int ret = FRACASSO;
	struct noFila *aux = p->cauda;

    if(p->cauda != NULL && p->frente != NULL) 
    {
       	memcpy(reg, &(p->frente->dados), p->tamInfo);

		if(aux == p->frente) 
		{ // caso tenha 1 elemento apenas
			free(p->frente);
			p->frente = p->cauda = NULL;
		}
		else 
		{	
            p->frente= p->frente->atras;
            free(p->frente->defronte); 
            p->frente->defronte = NULL;
		}
		ret = SUCESSO;
	}

	return ret;
}

/*************** BUSCA NA FRENTE ***************/
int buscaNaFrenteRM(info *reg, struct descFRM *p)
{  
    int ret = FRACASSO;

    if(p->frente != NULL && p->cauda != NULL) { 	
        memcpy(reg, &(p->frente->dados), p->tamInfo);
        ret = SUCESSO;
    }

    return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCaudaRM(info *reg, struct descFRM *p)
{
    int ret = FRACASSO;

    if(p->cauda != NULL && p->frente != NULL) {
        memcpy(reg, &(p->cauda->dados), p->tamInfo);
	    ret = SUCESSO;
    }

    return ret;
}

/*************** VAZIA? ***************/
int testaVaziaRM(struct descFRM *p)
{
    if(p->frente == NULL && p->cauda == NULL) {
        return SIM;
    }

    return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFilaRM(struct descFRM *p)
{ 
    int tam = 0;
    struct noFila *aux = p->cauda;

    while(aux != NULL) 
    { 	
		tam++;
        aux = aux->defronte;
    }

    return tam;
}

/*************** PURGA ***************/
int reiniciaRM(struct descFRM *p)
{   
    int ret=FRACASSO;
    struct noFila *aux=NULL;

    if(p->frente != NULL && p->cauda != NULL) 
    {  
        aux = p->cauda->defronte;
        while(aux != NULL) 
        {
            free(p->cauda);
            p->cauda = aux;
            aux = aux->defronte;
        }
        
        free(p->cauda);
        p->frente = NULL;
        p->refMov = NULL;
        p->cauda = NULL;
        ret=SUCESSO; 
    }
    return ret;	
}

/*************** DESTROI ***************/
struct descFRM * destroiRM(struct descFRM *p)
{
    reiniciaRM(p);
    free(p);
    return NULL; // aterra o ponteiro externo, declarado na aplica��o
}

struct noFila *buscaPelaDireita(struct descFRM *p,struct noFila *u, struct noFila *ref, int *mediaIt)
{
    struct noFila *aux = ref;
    while( aux->dados.rank >= u->dados.rank && aux->atras != NULL ) {
        aux = aux->atras;
        (*mediaIt)++;
    }
    
    u->defronte = aux->defronte;
    if( aux != p->frente )
        u->defronte->atras = u;
    u->atras = aux;
    aux->defronte = u;
    return u;
}

struct noFila *buscaPelaEsquerda(struct descFRM *p,struct noFila *u, struct noFila *ref, int *mediaIt){
    struct noFila *aux = ref;
    while(aux->dados.rank < u->dados.rank && aux->defronte != NULL ) {
        aux = aux->defronte;
        (*mediaIt)++;
    }
    
    u->defronte = aux;
    u->atras = aux->atras;
    if( aux != p->cauda )
        u->atras->defronte = u;
    aux->atras = u;

    return u;
}
