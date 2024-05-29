#include "FilaPrioridadeRM.h"
#include "FilaPrioridadeSemRM.h"
#include <time.h>

// codigo de shuffle feito por thejartender
void shuffle(info **array, size_t n)
{

    if (n > 1)
    {
        size_t i;
        for (i = n - 1; i > 0; i--)
        {
            size_t j = (unsigned int)((rand() % n) * (i + 1)) % n;
            info *t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main(int argc, char *argv[])
{
    info **arr;
    arr = malloc(10000 * sizeof(info *));
    if (argc < 2)
    {
        printf("Digite o nome do arquivo");
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen(argv[1], "rt");
    if (f == NULL)
    {
        printf("Falha em abrir arquivo.\n");
        return 1;
    }
    int nLinhas[18] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        info *val = malloc(sizeof(info));
        char matri[30], rank[30];
        fscanf(f, "%[^,]", val->nome);
        fscanf(f, ",%[^,]", matri);
        fscanf(f, ",%[^,]", rank);
        val->matricula = atoi(matri);
        val->rank = atoi(rank);
        fscanf(f, ",%[^\n]", val->curso);
        arr[i] = val;
    }

    shuffle(arr, 10000);
    struct descF *pq = cria(sizeof(info));
    struct descFRM *pqRM = criaRM(sizeof(info));

    // for(int i = 0; i< 10000; i++){
    //     printf("%s,%i,%i,%s",arr[i]->nome,arr[i]->matricula,arr[i]->rank,arr[i]->curso);
    // }

    // int n = nLinhas[rand()%18], interpq=0, interpqRM = 0;
    int n = 0, interpq = 0, interpqRM = 0;
    double mediapq[10000], mediapqRM[10000];
    // printf("Total de linhas lidas: %i\n", n);
    for (int i = 0; i < 10000; i++)
    {
        interpq += insere(arr[i],pq);
        interpqRM += insereRM(arr[i], pqRM);
        mediapq[i] = (double)interpq/(i+1);
        mediapqRM[i] = (double)interpqRM/(i+1);
    }

    FILE *outputpq = fopen("mediapq.txt","wt");
    FILE *outputRM = fopen("mediapqRM.txt","wt");
    if(outputpq==NULL || outputRM==NULL){
        printf("falha em arquivo\n");
        fclose(outputpq);
        fclose(outputRM);
        fclose(f);
        return 1;
    }
    fflush(outputpq);
    fflush(outputRM);
    for (int i = 0; i < 10000; i++)
    {
        fprintf(outputpq,"%.2lf\n",mediapq[i]);
        fprintf(outputRM,"%.2lf\n",mediapqRM[i]);
    }


    fclose(outputRM);
    fclose(outputpq);
    fclose(f);
    // printf("Total interacoes fila simples: %i Media: %.2f\n", interpq, (float)interpq / n);
    // printf("Total interacoes fila com Referencial Movel: %i Media: %.2f\n", interpqRM, (float)interpqRM / n);

    return 0;
}