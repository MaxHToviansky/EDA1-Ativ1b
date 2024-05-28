#ifndef NOS_H
#define NOS_H

typedef struct dados{ 
	int matricula, rank;
	char nome[30], curso[30];
}info;


struct noFila { 
	info dados;
	struct noFila *atras;
    struct noFila *defronte;
};
#endif