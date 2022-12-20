#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct elem{
    char string[30];
    struct elem *prox;    
}Elem;

typedef struct fila{
    Elem *primeiro;
    Elem *ultimo;
}Fila;

typedef struct pilha{
    Elem *topo;
}Pilha;

void criarF(Fila *x);
bool vaziaF(Fila *x);
bool inserir(Fila *x, char *string);
bool retirar(Fila *x, char *string);
void criarP(Pilha *x);
bool vaziaP(Pilha *x);
bool empilha(Pilha *x, char *string);
bool desempilha(Pilha *x, char *string);
void imprimeF(Fila *x);
void imprimeP(Pilha *x);

int main(){
    // Abertura do arquivo para leitura e/ou escrita.
    FILE *arquivo = fopen("arquivo.txt", "rb+");
    if (arquivo == NULL) {
        arquivo = fopen("arquivo.txt", "wb+");
        if (arquivo == NULL) {
            printf("Nao foi possivel abrir o arquivo.\n");
            exit(1);
        }
    }
    // Inicialização das variáveis.
    Fila *f = (Fila*) malloc(sizeof(Fila));
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(f == NULL || p == NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
    criarF(f);
    criarP(p);
    char *str = (char*) malloc(30*sizeof(char));

    // Liberando as Filas e Pilhas e fechando o arquivo.
    free(f);
    free(p);
    fclose(arquivo);
    return 0;
}

void criarF(Fila *x){
    if(x != NULL){
        x->primeiro = NULL;
        x->ultimo = NULL;
    }
}

bool vaziaF(Fila *x){
    if(x->primeiro == NULL){
        return true;
    }else{
        return false;
    }
}

bool inserir(Fila *x, char *string){
    Elem *y = (Elem*) malloc(sizeof(Elem));
    if(y == NULL){
        return false;
    }else{
        strcpy(y->string, string);
        y->prox = NULL;
        if(x->primeiro == NULL){
            x->primeiro = y;
        }else{
            x->ultimo->prox = y;
        }
        x->ultimo = y;
        return true;
    }
}

bool retirar(Fila *x, char *string){
    Elem *y = x->primeiro;
    if(y == NULL){
        return false;
    }else{
        x->primeiro = y->prox;
        y->prox = NULL;
        strcpy(string, y->string);
        free(y);
        if(x->primeiro == NULL){
            x->ultimo = NULL;
        }
        return true;
    }
}

void criarP(Pilha *x){
    x->topo = NULL;
}

bool vaziaP(Pilha *x){
    if(x->topo == NULL){
        return true;
    }else{
        return false;
    }
}

bool empilha(Pilha *x, char *string){
    Elem *y = (Elem*) malloc(sizeof(Elem));
    if(y != NULL){
        strcpy(y->string, string);
        y->prox = x->topo;
        x->topo = y;
        return true;
    }else{
        return false;
    }
}

bool desempilha(Pilha *x, char *string){
    if(!vaziaP(x)){
        Elem *y = x->topo;
        x->topo = y->prox;
        y->prox = NULL;
        strcpy(string, y->string);
        free(y);
        return true;
    }else{
        return false;
    }
}

void imprimeF(Fila *x){
    char *str = (char*) malloc(30*sizeof(char));
    while (!vaziaF(x)){
        retirar(x, str);
        printf("%s\n", str);
    }
}

void imprimeP(Pilha *x){
    char *str = (char*) malloc(30*sizeof(char));
    while (!vaziaP(x)){
        desempilha(x, str);
        printf("%s\n", str);
    }
}