#include "FilaPrioridadeRM.h"
#include "FilaPrioridadeSemRM.h"
#include <time.h>

//codigo de shuffle feito por thejartender
void shuffle(info **array, size_t n) {    

    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) ((rand()%n)*(i+1))%n;
            info *t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
} 


int main( int argc, char *argv[] ){
    info **arr;
    arr = malloc(10000*sizeof(info*));
    if( argc < 2 ) {
        printf("Digite o nome do arquivo");
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen( argv[1], "rt");
    if(f==NULL){
        printf("Falha em abrir arquivo.\n");
        return 1;
    }
    int nLinhas[18] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    srand(time(NULL));
    for(int i =0 ; i <10000;i++){
        info *val = malloc(sizeof(info));
        char matri[30], rank[30];
        fscanf(f,"%[^,]",val->nome);
        fgetc(f);
        fscanf(f,"%[^,]",matri);
        fgetc(f);
        fscanf(f,"%[^,]",rank);
        fgetc(f);
        val->matricula = atoi(matri);
        val->rank = atoi(rank);
        fscanf(f,"%[^\n]",val->curso);
        arr[i] = val;
    }

    shuffle(arr,10000);
    struct descF *pq = cria(sizeof(info));
    struct descFRM *pqRM = criaRM(sizeof(info));
    
    int n = nLinhas[rand()%18], interpq=0, interpqRM = 0;
    for(int i = 0; i < n; i++){
        interpq += insere(arr[i],pq);
        interpqRM += insereRM(arr[i],pqRM);
    }

    printf("Total interacoes fila simples: %i Media: %f\n",interpq,interpq/n);
    printf("Total interacoes fila simples: %i Media: %f\n",interpqRM,interpqRM/n);

    return 0;
}