#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    * Definicao da estrutura de dados ElementoId.
    * - 1 inteiro que representa o id de um item do cardápio.
    * - 1 ponteiro para o próximo ElementoId.
*/
typedef struct elementoId{
    int id;
    struct elementoId *prox;    
}ElementoId;

/*
    * Definicao da estrutura de dados Pilha.
    * - 1 ponteiro para o ElementoId que esta no topo da Pilha.
*/
typedef struct pilhaId{
    ElementoId *topo;
}PilhaId;

/*
    * Definicao da estrutura de dados Cliente.
    * - 1 string para o nome do Cliente.
    * - 1 ponteiro para PilhaId para os itens comprados pelo Cliente.
    * - 1 ponteiro para o próximo Cliente.
*/

typedef struct cliente{
    char nome[30];
    PilhaId *x;
    struct cliente *prox;
}Cliente;

/*
    * Definicao da estrutura de dados Fila.
    * - 1 ponteiro para o primeiro Cliente da Fila.
    * - 1 ponteiro para o ultimo Cliente da Fila.
*/
typedef struct fila{
    Cliente *primeiro;
    Cliente *ultimo;
}Fila;

/*
    * Definicao da estrutura de dados Item.
    * - 1 int para o id do item.
    * - 1 vetor de char de 50 posicoes para a descricao do item.
    * - 1 float para o preco do item.
*/
typedef struct item{
    int id;
    char descricao[50];
    float preco;
}Item;

void criarF(Fila *x);
void destruirF(Fila *x);
bool vaziaF(Fila *x);
bool inserir(Fila *x, char *string, PilhaId *p);
bool retirar(Fila *x, char *string, PilhaId *p);
void criarPId(PilhaId *x);
void destruirP(PilhaId *x);
bool vaziaPId(PilhaId *x);
bool empilhaId(PilhaId *x, int id);
bool desempilhaPId(PilhaId *x, int *id);
void imprimeF(Fila *x);
void imprimePId(PilhaId *x);
void insereCardapio(int id, char *descricao, float preco, int indice, Item *vetor);
void imprimeCardapio(Item *cardapio);
void empilhaChocolates(PilhaId *x, char *str);
void inserirCliente(Item *cardapio, Fila *f);

int main(){
    // Inicialização das variáveis.
    Fila *f = (Fila*) malloc(sizeof(Fila));
    PilhaId *p = (PilhaId*) malloc(sizeof(PilhaId));
    if(f == NULL || p == NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
    Item *cardapio = (Item*) malloc(10*sizeof(Item));
    char *str = (char*) malloc(30*sizeof(char));
    criarF(f);
    criarPId(p);

    // Iniciando o cardapio.
    insereCardapio(1, "Pizza Bacon", 29.99, 0, cardapio);
    insereCardapio(2, "Pizza Marguerita", 34.99, 1, cardapio);
    insereCardapio(3, "Pizza Frango e Catupiry", 39.99, 2, cardapio);
    insereCardapio(4, "Pizza 4 Queijos", 44.99, 3, cardapio);
    insereCardapio(5, "Pizza Moda", 49.99, 4, cardapio);
    insereCardapio(6, "Refrigerante Lata", 5, 5, cardapio);
    insereCardapio(7, "Refrigerante 2L", 7, 6, cardapio);
    insereCardapio(8, "Suco 500ml", 8, 7, cardapio);
    insereCardapio(9, "Suco 1L", 15, 8, cardapio);
    insereCardapio(10, "Cerveja Lata", 5, 9, cardapio);

    // Menu do restaurante
    int opcao;
    do{
        printf("0 - Sair\n1 - Imprimir cardapio\n2 - Inserir Cliente na Fila\n3 - Fazer chekout de todos os clientes da fila\n");
        scanf(" %d", &opcao);

        switch(opcao){
            case 0:
                printf("Obrigado pela atencao, ate mais!\n");
                break;
            case 1:
                imprimeCardapio(cardapio);
                break;
            case 2:
                inserirCliente(cardapio, f);
                break;
            case 3:
                imprimeF(f);
                break;
            case 4:
                //empilhaChocolate(p, str);
                //printf("\nChocolates adiconados:\n");
                //imprimeP(p);
                //printf("\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);
   
    // Liberando memória.
    destruirF(f);
    destruirP(p);
    free(cardapio);
    free(str);
   
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
bool inserir(Fila *x, char *string, PilhaId *p){
    Cliente *y = (Cliente*) malloc(sizeof(Cliente));
    if(y == NULL){
        return false;
    }else{
        strcpy(y->nome, string);
        y->x = (PilhaId*) malloc(sizeof(PilhaId));
        criarPId(y->x);
        y->x->topo = p->topo;
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
bool retirar(Fila *x, char *string, PilhaId *p){
    Cliente *y = x->primeiro;
    if(y == NULL){
        return false;
    }else{
        x->primeiro = y->prox;
        y->prox = NULL;
        strcpy(string, y->nome);
        p->topo = y->x->topo;
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
void criarPId(PilhaId *x){
    x->topo = NULL;
}

/*
    * Nome: destruirP.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Caso a Pilha inserida exista, e desalocada.
*/
void destruirP(PilhaId *x){
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
bool vaziaPId(PilhaId *x){
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
bool empilhaId(PilhaId *x, int id){
    ElementoId *y = (ElementoId*) malloc(sizeof(ElementoId));
    if(y != NULL){
        y->id = id;
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
bool desempilhaPId(PilhaId *x, int *id){
    if(!vaziaPId(x)){
        ElementoId *y = x->topo;
        x->topo = y->prox;
        y->prox = NULL;
        *id = y->id;
        free(y);
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: imprimeF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Cria um ponteiro para char de 30 posicoes, e, enquanto a Fila nao estiver vazia, retira um Id e coloca
    seu valor no ponteiro de char criado e o imprime.
*/
void imprimeF(Fila *x){
    if(vaziaF(x)){
        printf("Fila Vazia.\n");
    }else{
        PilhaId *p = (PilhaId*) malloc(sizeof(PilhaId));
        criarPId(p);
        char *nome = (char*) malloc(30*sizeof(char));
        int id;
        while (!vaziaF(x)){
            retirar(x, nome, p);
            printf("\nNome: %s\nItens: ");
            while(!vaziaPId(p)){
                desempilhaPId(p, &id);
                printf("%d ", id);
            }
            printf("\n");
        }
        free(p);
        free(nome);
    }
}

/*
    * Nome: imprimeP.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Cria um ponteiro para char de 30 posicoes, e, enquanto a Pilha nao estiver vazia, desempilha um Elemento e coloca
    seu valor no ponteiro de char criado e o imprime.
*/
void imprimePId(PilhaId *x){
    int y;
    while (!vaziaPId(x)){
        desempilhaPId(x, &y);
        printf("%d\n", y);
    }
}

/*
    * Nome: insereCardapio.
    * Entrada: 1 int para o id, 1 ponteiro para char com a descricao, 1 float para o preco e 1 int para o indice no vetor, 1 ponteiro
    * para o vetor de Itens.
    * Processo: Insere no vetor de Itens as informacoes passadas.
*/
void insereCardapio(int id, char *descricao, float preco, int indice, Item *vetor){
    vetor[indice].id = id;
    strcpy(vetor[indice].descricao, descricao);
    vetor[indice].preco = preco;
}

 void imprimeCardapio(Item *vetor){
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("\t%d. %s - %.2f", vetor[i].id, vetor[i].descricao, vetor[i].preco);
        printf("\n");
    }
    printf("\n");
}

/*void empilhaChocolates(Pilha *x, char *str){
    do{
        fflush(stdin);
        printf("Adicione um chocolate a pilha: ");
        gets(str);
        empilha(x, str);
        printf("\n\tDeseja continuar adicionando?\n\t1- Sim    0 - Nao\n");
    }while(getch() == '1');
}
*/

void inserirCliente(Item *cardapio, Fila *f){
    PilhaId *x = (PilhaId*) malloc(sizeof(PilhaId));
    criarPId(x);
    char *nome = (char*) malloc(30*sizeof(char));
    int id, ctrl = 1;
    printf("Insira seu nome: ");fflush(stdin);
    gets(nome);
    imprimeCardapio(cardapio);
    do{
        printf("Escolhe um item do cardapio: ");
        scanf(" %d", &id);
        empilhaId(x, id);
        printf("Mais alguma coisa? 1-Sim | 0-Nao ");
        scanf(" %d", &ctrl);
    }while(ctrl != 0);
    inserir(f, nome, x);
    free(x);
    free(nome);
}
