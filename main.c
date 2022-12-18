#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct elemF{
    int valor;
    struct elemF *prox;    
}ElemF;

typedef struct fila{
    ElemF *primeiro;
    ElemF *ultimo;
}Fila;

typedef struct elemP{
    int valor;
    struct elemP *prox;
}ElemP;

typedef struct pilha{
    ElemP *topo;
}Pilha;

void criarF(Fila *x);
bool vaziaF(Fila *x);
bool inserir(Fila *x, int valor);
bool retirar(Fila *x, int *valor);
void criarP(Pilha *x);
bool vaziaP(Pilha *x);
bool empilha(Pilha *x, int valor);
bool desempilha(Pilha *x, int *valor);

int main(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    criarF(f);
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    criarP(p);
    if(f == NULL || p == NULL){
        exit(1);
    }
    int x;
    fflush(stdin);
    for(int i = 0; i < 10; i++){
        scanf(" %d", &x);
        empilha(p, x);
        inserir(f, x);
    }
    printf("Pilha: ");
    while(!vaziaP(p)){
        desempilha(p, &x);
        printf("%d ", x);
    }
    printf("\nFila: ");
    while(!vaziaF(f)){
        retirar(f, &x);
        printf("%d ", x);
    }
    printf("\n");

    free(f);
    free(p);
    return 0;
}

void criarF(Fila *x){
    x->primeiro = NULL;
    x->ultimo = NULL;
}

bool vaziaF(Fila *x){
    if(x->primeiro == NULL){
        return true;
    }else{
        return false;
    }
}

bool inserir(Fila *x, int valor){
    ElemF *y = (ElemF*) malloc(sizeof(ElemF));
    if(y == NULL){
        return false;
    }else{
        y->valor = valor;
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

bool retirar(Fila *x, int *valor){
    ElemF *y = x->primeiro;
    if(y == NULL){
        return false;
    }else{
        x->primeiro = y->prox;
        y->prox = NULL;
        *valor = y->valor;
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

bool empilha(Pilha *x, int valor){
    ElemP *y = (ElemP*) malloc(sizeof(ElemP));
    if(y != NULL){
        y->valor = valor;
        y->prox = x->topo;
        x->topo = y;
        return true;
    }else{
        return false;
    }
}

bool desempilha(Pilha *x, int *valor){
    if(!vaziaP(x)){
        ElemP *y = x->topo;
        x->topo = y->prox;
        y->prox = NULL;
        *valor = y->valor;
        free(y);
        return true;
    }else{
        return false;
    }
}