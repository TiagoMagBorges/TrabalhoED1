#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    * Definicao da estrutura de dados Elemento.
    * - 1 vetor de char de 30 posicoes.
    * - 1 ponteiro para o próximo Elemento.
*/
typedef struct elemento{
    char string[30];
    struct elemento *prox;    
}Elemento;

/*
    * Definicao da estrutura de dados Fila.
    * - 1 ponteiro para o primeiro Elemento da Fila.
    * - 1 ponteiro para o ultimo Elemento da Fila.
*/
typedef struct fila{
    Elemento *primeiro;
    Elemento *ultimo;
}Fila;

/*
    * Definicao da estrutura de dados Pilha.
    * - 1 ponteiro para o Elemento que esta no topo da Pilha.
*/
typedef struct pilha{
    Elemento *topo;
}Pilha;

void criarF(Fila *x);
void destruirF(Fila *x);
bool vaziaF(Fila *x);
bool inserir(Fila *x, char *string);
bool retirar(Fila *x, char *string);
void criarP(Pilha *x);
void destruirP(Pilha *x);
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
    // Item *cardapio = (Item*) malloc(x*sizeof(Item));
    criarF(f);
    criarP(p);
    char *str = (char*) malloc(30*sizeof(char));

    // Liberando as Filas e Pilhas e fechando o arquivo.
    destruirF(f);
    destruirP(p);
    fclose(arquivo);
    return 0;
}

/*
    * Nome: criarF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Caso a Fila inserida exista, atribui NULL aos ponteiros para primeiro
    e ultimo Elementos da Fila.
*/
void criarF(Fila *x){
    if(x != NULL){
        x->primeiro = NULL;
        x->ultimo = NULL;
    }
}

/*
    * Nome: destruirF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Caso a Fila inserida exista, e desalocada.
*/
void destruirF(Fila *x){
    if(x != NULL){
        free(x);
    }
}

/*
    * Nome: vaziaF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Verifica se a Fila esta vazia checando se o primeiro Elemento e NULL.
    * Saida: True caso o primeiro seja NULL, False caso contrario.
*/
bool vaziaF(Fila *x){
    if(x->primeiro == NULL){
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: inserir.
    * Entrada: 1 ponteiro para Fila e 1 ponteiro para char.
    * Processo: Cria um ponteiro para Elemento e atribui a ele o ponteiro para char inserido e NULL 
    para o proximo Elemento. Checa se a fila esta vazia, se sim, atribui o ponteiro Elemento criado
    para o primeiro Elemento da Fila, e caso não esteja vazia, atribui ao ultimo Elemento da Fila.
    * Saida: True caso a operacao tenha funcionado, False caso contrario.
*/
bool inserir(Fila *x, char *string){
    Elemento *y = (Elemento*) malloc(sizeof(Elemento));
    if(y == NULL){
        return false;
    }else{
        strcpy(y->string, string);
        y->prox = NULL;
        if(vaziaF(x)){
            x->primeiro = y;
        }else{
            x->ultimo->prox = y;
        }
        x->ultimo = y;
        return true;
    }
}

/*
    * Nome: retirar.
    * Entrada: 1 ponteiro para Fila e 1 ponteiro para char.
    * Processo: Cria um ponteiro para Elemento e aponta ele para primeiro Elemento da Fila. Checa se a fila esta vazia,
    se não estiver, o primeiro da Fila vai receber o próximo do Elemento criado que vai apontar para NULL. Em sequencia
    o vetor de char e copiado para o ponteiro para char inserido na funcao. O Elemento alocado e desalocado, e faz-se um
    ultimo teste para testar se o primeiro da fila e NULL, caso seja true, o ultimo tambem recebe NULL.
    * Saida: True caso a operacao tenha funcionado, False caso contrario.
*/
bool retirar(Fila *x, char *string){
    Elemento *y = x->primeiro;
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

/*
    * Nome: criarP.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Caso a Pilha inserida exista, atribui NULL ao ponteiro de Elemento topo.
*/
void criarP(Pilha *x){
    x->topo = NULL;
}

/*
    * Nome: destruirP.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Caso a Pilha inserida exista, e desalocada.
*/
void destruirP(Pilha *x){
    if(x != NULL){
        free(x);
    }
}

/*
    * Nome: vaziaP.
    * Entrada: 1 ponteiro de Pilha
    * Processo: Verifica se a Pilha esta vazia checando se o Elemento topo e NULL.
    * Saida: True caso o topo seja NULL, False caso contrario.
*/
bool vaziaP(Pilha *x){
    if(x->topo == NULL){
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: empilha.
    * Entrada: 1 ponteiro para Pilha e 1 ponteiro para char.
    * Processo: Cria um Elemento, atribui a ele o ponteiro de char inserido na funcao e aponta o proximo parao topo
    da pilha, que por sua vez aponta para o Elemento criado.
    * Saida: True caso a operacao tenha funcionado, False caso contrario.
*/
bool empilha(Pilha *x, char *string){
    Elemento *y = (Elemento*) malloc(sizeof(Elemento));
    if(y != NULL){
        strcpy(y->string, string);
        y->prox = x->topo;
        x->topo = y;
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: desempilha.
    * Entrada: 1 ponteiro para Pilha e 1 ponteiro para char.
    * Processo: Testa se a Pilha esta vazia, se não estiver, cria um ponteiro para Elemento e aponta ele para o topo da 
    Pilha. Em seguida, o topo da Pilha vai apontar para o proximo do Elemento criado, que vai apontar para NULL. Em sequencia
    o vetor de char e copiado para o ponteiro para char inserido na funcao, e o Elemento criado e desalocado.
    * Saida: True caso a operacao tenha funcionado, False caso contrario.
*/
bool desempilha(Pilha *x, char *string){
    if(!vaziaP(x)){
        Elemento *y = x->topo;
        x->topo = y->prox;
        y->prox = NULL;
        strcpy(string, y->string);
        free(y);
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: imprimeF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Cria um ponteiro para char de 30 posicoes, e, enquanto a Fila nao estiver vazia, retira um Elemento e coloca
    seu valor no ponteiro de char criado e o imprime.
*/
void imprimeF(Fila *x){
    char *str = (char*) malloc(30*sizeof(char));
    while (!vaziaF(x)){
        retirar(x, str);
        printf("%s\n", str);
    }
}

/*
    * Nome: imprimeP.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Cria um ponteiro para char de 30 posicoes, e, enquanto a Pilha nao estiver vazia, desempilha um Elemento e coloca
    seu valor no ponteiro de char criado e o imprime.
*/
void imprimeP(Pilha *x){
    char *str = (char*) malloc(30*sizeof(char));
    while (!vaziaP(x)){
        desempilha(x, str);
        printf("%s\n", str);
    }
}