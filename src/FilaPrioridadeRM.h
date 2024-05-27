#define LIVRE 0
#define OCUPADA 1
#define FRACASSO 0
#define SUCESSO 1
#define FALSO 0
#define VERDADEIRO 1
#define NAO 0
#define SIM 1
#define MAIOR 1
#define IGUAL 0
#define MENOR -1
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define debugging  1

#include "Nos.h"

struct descFRM { 	
	struct noFila *frente;
    struct noFila *refMov;
	struct noFila *cauda;
    int tamInfo;
};


//======================APLICACAO=====================


//======================FILA=====================
struct descFRM * criaRM(int tamInfo);
int insereRM(info *novo,struct descFRM *p);
int tamanhoDaFilaRM(struct descFRM *p);
int reiniciaRM(struct descFRM *p);
struct descFRM * destroiRM(struct descFRM *p);
int buscaNaCaudaRM(info *reg, struct descFRM *p);
int buscaNaFrenteRM(info *reg, struct descFRM *p);
int remove_RM(info *reg, struct descFRM *p);
int testaVaziaRM(struct descFRM *p);
int inverteRM(struct descFRM *p);
struct noFila *buscaPelaDireita(struct descFRM *p,struct noFila *u, struct noFila *ref, int *mediaIt);
struct noFila *buscaPelaEsquerda(struct descFRM *p,struct noFila *u, struct noFila *ref, int *mediaIt);

