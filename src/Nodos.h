
typedef struct node
{
    Node *front,*back;
    Data *info; 
} Node;

typedef struct info
{
    int rank, matricula;
    char *nome, *curso;
} Data;

Node *createNode();
