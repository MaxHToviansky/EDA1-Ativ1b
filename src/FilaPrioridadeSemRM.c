#include "FilaPrioridadeSemRM.h"



/*************** CRIA ***************/
struct descF * cria(int tamInfo)
{   	
    struct descF *desc = (struct descF*) malloc(sizeof(struct descF));
    if(desc != NULL) {
        desc->cauda = NULL;
        desc->frente = NULL;
		desc->tamInfo= tamInfo;
    }
    return desc;
}

/*************** INSERE A PARTIR DA FRENTE ***************/
int insere(info *pInfo, struct descF *p)
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
        { // 
            if(novoNoFila->dados.rank < p->cauda->dados.rank) /*novo elemento � o de menor prior rank */
            { 	
                novoNoFila->atras=NULL;
                novoNoFila->defronte=p->cauda;
                p->cauda->atras=novoNoFila;
                p->cauda=novoNoFila;
                    
            }
            else
            {    	 
                visitado = p->frente; /*maior prior rank na frente */
                while(visitado->atras != NULL && (visitado->dados.rank >= novoNoFila->dados.rank)) {
                    visitado= visitado->atras; /* A(rank) <= B(rank) */
                    mediaIt++;
                }

                if(visitado->dados.rank < novoNoFila->dados.rank)   /* novo item fica a frente do visitado */
                {   	
                    novoNoFila->atras = visitado;
                    if (visitado->defronte != NULL)
                    {      
                        novoNoFila->defronte = visitado->defronte;
                        visitado->defronte->atras = novoNoFila;
                    } 
                    else // novo item � o de maior prior rank de todos na fila, sendo a nova frente
                    {  
                        novoNoFila->defronte = NULL;      
                        p->frente = novoNoFila;
                    }	   
                    visitado->defronte = novoNoFila;  
                }	
                //else //<<- novo item � o de menor prior rank de todos na fila, sendo a nova cauda
                    //Essa � uma condicao ja tratada 
                    //{
                    //		novoNoFila->defronte = visitado;
                    //		novoNoFila->atras = NULL;
                    //		visitado->atras = novoNoFila;
                    //		p->cauda = novoNoFila; 
                    //}	
            }   
                
        }//
        return mediaIt;
    }
    
	return FRACASSO;

}


/*************** REMOVE DA FRENTE ***************/
int remove_(info *reg, struct descF  *p)
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
int buscaNaFrente(info *reg, struct descF *p)
{  
    int ret = FRACASSO;

    if(p->frente != NULL && p->cauda != NULL) { 	
        memcpy(reg, &(p->frente->dados), p->tamInfo);
        ret = SUCESSO;
    }

    return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCauda(info *reg, struct descF *p)
{
    int ret = FRACASSO;

    if(p->cauda != NULL && p->frente != NULL) {
        memcpy(reg, &(p->cauda->dados), p->tamInfo);
	    ret = SUCESSO;
    }

    return ret;
}

/*************** VAZIA? ***************/
int testaVazia(struct descF *p)
{
    if(p->frente == NULL && p->cauda == NULL) {
        return SIM;
    }

    return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFila(struct descF *p)
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
int reinicia(struct descF *p)
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
        p->cauda = NULL;
        ret=SUCESSO; 
    }
    return ret;	
}

/*************** DESTROI ***************/
struct descF * destroi(struct descF *p)
{
    reinicia(p);
    free(p);
    return NULL; // aterra o ponteiro externo, declarado na aplica��o
}
