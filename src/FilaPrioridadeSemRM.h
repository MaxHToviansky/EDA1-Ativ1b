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
#include "Nos.h"
#define debugging  1



struct descF { 	
	struct noFila *frente;
	struct noFila *cauda;
    int tamInfo;
};


//======================APLICACAO=====================


//======================FILA=====================
struct descF * cria(int tamInfo);
int insere(info *novo,struct descF *p);
int tamanhoDaFila(struct descF *p);
int reinicia(struct descF *p);
struct descF * destroi(struct descF *p);
int buscaNaCauda(info *reg, struct descF *p);
int buscaNaFrente(info *reg, struct descF *p);
int remove_(info *reg, struct descF *p);
int testaVazia(struct descF *p);
int inverte(struct descF *p);

