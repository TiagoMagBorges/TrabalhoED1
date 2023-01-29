#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/*
    * Definição da estrutura de dados ElementoId.
    * - 1 int que representa o id de um item do cardápio.
    * - 1 ponteiro para o próximo ElementoId.
*/
typedef struct elementoId{
    int id;
    struct elementoId *prox;    
}ElementoId;

/*
    * Definição da estrutura de dados Pilha.
    * - 1 ponteiro para o ElementoId que está no topo da Pilha.
*/
typedef struct pilhaId{
    ElementoId *topo;
}PilhaId;

/*
    * Definição da estrutura de dados Cliente.
    * - 1 string para o nome do Cliente.
    * - 1 ponteiro para PilhaId que armazena os itens comprados pelo Cliente.
    * - 1 ponteiro para o próximo Cliente.
*/

typedef struct cliente{
    char nome[30];
    PilhaId *x;
    struct cliente *prox;
}Cliente;

/*
    * Definição da estrutura de dados Fila.
    * - 1 ponteiro para o primeiro Cliente da Fila.
    * - 1 ponteiro para o último Cliente da Fila.
*/
typedef struct fila{
    Cliente *primeiro;
    Cliente *ultimo;
}Fila;

/*
    * Definição da estrutura de dados Item.
    * - 1 int para o id do item.
    * - 1 vetor para char de 50 posições para a descrição do item.
    * - 1 float para o preço do item.
*/
typedef struct item{
    int id;
    char descricao[50];
    float preco;
}Item;

/*
    * Definição da estrutura de dados Chocolate.
    * - 1 vetor de 30 caracteres para o nome do chocolate.
    * - 1 ponteiro para o próximo chocolate.
*/
typedef struct chocolate{
    char nome[30];
    struct chocolate *prox;
}Chocolate;

/*
    * Definição da estrutura de dados PilhaChoc.
    * - 1 ponteiro para o topo da Pilha de chocolates.
*/
typedef struct pilhaChoc{
    Chocolate *topo;
}PilhaChoc;


void criarF(Fila *x);
void destruirF(Fila *x);
bool vaziaF(Fila *x);
bool inserir(Fila *x, char *string, PilhaId *p);
bool retirar(Fila *x, char *string, PilhaId *p);
void criarPId(PilhaId *x);
void destruirPId(PilhaId *x);
bool vaziaPId(PilhaId *x);
bool empilhaId(PilhaId *x, int id);
void criarPC(PilhaChoc *x);
void destruirPC(PilhaChoc *x);
bool vaziaPC(PilhaChoc *x);
bool empilhaC(PilhaChoc *x, char *nome);
bool desempilhaC(PilhaChoc *x, char *nome);
void imprimeF(Fila *x, Item *cardapio, PilhaChoc *pC);
void imprimePId(PilhaId *x);
void insereCardapio(int id, char *descricao, float preco, int indice, Item *vetor);
void imprimeCardapio(Item *cardapio);
void inserirCliente(Item *cardapio, Fila *f, PilhaChoc *pC, Chocolate *vetor);
void itemCardapio(int id, char *nomecomida, float *precoUnitario, Item *cardapio);
void clientesAleatorios(Fila *f, Item *cardapio, Chocolate *vetor, PilhaChoc *pC, int qtd);
void cabecalho();

int main(){
    // Inicialização das variáveis.
    Fila *f = (Fila*) malloc(sizeof(Fila));
    PilhaId *p = (PilhaId*) malloc(sizeof(PilhaId));
    PilhaChoc *pC = (PilhaChoc*) malloc(sizeof(PilhaChoc));
    if(f == NULL || p == NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
    Item *cardapio = (Item*) malloc(10*sizeof(Item));
    char *str = (char*) malloc(30*sizeof(char));
    int x;
    criarF(f);
    criarPId(p);
    criarPC(pC);

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

    // Chocolates
    Chocolate *vetor = (Chocolate*) malloc(10*sizeof(Chocolate));
    strcpy(vetor[0].nome, "Lolo");
    strcpy(vetor[1].nome, "Kit Kat");
    strcpy(vetor[2].nome, "Sonho de Valsa");
    strcpy(vetor[3].nome, "Chokito");
    strcpy(vetor[4].nome, "Diamante Negro");
    strcpy(vetor[5].nome, "Ouro Branco");
    strcpy(vetor[6].nome, "Suflair");
    strcpy(vetor[7].nome, "Ferrero Rocher");
    strcpy(vetor[8].nome, "Bis");
    strcpy(vetor[9].nome, "Batom");

    // Menu do restaurante
    cabecalho();

    int opcao;
    do{
        printf("\n0 - Sair\n1 - Imprimir cardapio\n2 - Inserir Cliente na Fila\n3 - Fazer chekout de todos os clientes da fila\n4 - Gerar clientes automaticamente\n");
        scanf(" %d", &opcao);

        switch(opcao){
            case 0:
                printf("Obrigado pela atencao, ate mais!\n");
                break;
            case 1:
                imprimeCardapio(cardapio);
                break;
            case 2:
                inserirCliente(cardapio, f, pC, vetor);
                break;
            case 3:
                imprimeF(f, cardapio, pC);
                break;
            case 4:
                printf("Numero de clientes a ser gerado: ");
                scanf(" %d", &x);fflush(stdin);
                clientesAleatorios(f, cardapio, vetor, pC, x);
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);
   
    // Liberando memória.
    destruirF(f);
    destruirPId(p);
    free(cardapio);
    free(str);
   
    return 0;
}

/*
    * Nome: criarF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Caso a Fila inserida exista, atribui NULL aos ponteiros para primeiro
    e último Elemento da Fila.
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
    * Processo: Caso a Fila inserida exista, é desalocada.
*/
void destruirF(Fila *x){
    if(x != NULL){
        free(x);
    }
}

/*
    * Nome: vaziaF.
    * Entrada: 1 ponteiro para Fila.
    * Processo: Verifica se a Fila está vazia checando se o primeiro Elemento é NULL.
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
    * Processo: - Cria um ponteiro para Cliente e atribui ao seu campo ->nome a string inserida;
                - O topo da PilhaId é inserida para o topo da pilha do Cliente criada;
                - NULL para o próximo Cliente;
                - Checa se a fila esta vazia, se sim, atribui o ponteiro Cliente criado para o primeiro Cliente da Fila
                  e, caso não esteja vazia, atribui ao último Cliente da Fila.
    * Saida: True caso a operação tenha funcionado, False caso contrario.
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
    * Processo: - Cria um ponteiro para Cliente e aponta ele para primeiro Cliente da Fila;
                - Checa se a fila está vazia, se não estiver, o primeiro da Fila vai receber o próximo do Cliente 
                  criado que vai apontar para NULL;
                - Em sequência, o vetor de char é copiado para o ponteiro char inserido na função;
                - O Cliente alocado é desalocado, e faz-se um último teste para checar se o primeiro da fila é NULL, 
                  caso seja true, o último também recebe NULL.
    * Saida: True caso a operação tenha funcionado, False caso contrário.
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
    * Nome: criarPId.
    * Entrada: 1 ponteiro para PilhaId.
    * Processo: Caso a PilhaId inserida exista, atribui NULL ao ponteiro de Elemento topo.
*/
void criarPId(PilhaId *x){
    x->topo = NULL;
}

/*
    * Nome: destruirPId.
    * Entrada: 1 ponteiro para PilhaId.
    * Processo: Caso a Pilha inserida exista, é desalocada.
*/
void destruirPId(PilhaId *x){
    if(x != NULL){
        free(x);
    }
}

/*
    * Nome: vaziaPId.
    * Entrada: 1 ponteiro de PilhaId.
    * Processo: Verifica se a Pilha está vazia checando se o Elemento topo é NULL.
    * Saida: True caso o topo seja NULL, False caso contrário.
*/
bool vaziaPId(PilhaId *x){
    if(x->topo == NULL){
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: empilhaId.
    * Entrada: 1 ponteiro para Pilha e 1 int para o id do item no cardápio.
    * Processo: Cria um Elemento, atribui a ele o int inserido na função e aponta o próximo para o topo
                da pilha, que por sua vez aponta para o Elemento criado.
    * Saida: True caso a operação tenha funcionado, False caso contrário.
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
    * Nome: desempilhaId.
    * Entrada: 1 ponteiro para Pilha e 1 int para o id do item no cardápio.
    * Processo: - Testa se a Pilha está vazia, se não estiver, cria um ponteiro para Elemento e aponta ele para o topo da 
                  Pilha;
                - Em seguida, o topo da Pilha vai apontar para o proximo do Elemento criado, que vai apontar para NULL;
                - Em sequencia, o int id do Elemento é copiado para o int id inserido na função, e o Elemento criado 
                  é desalocado.
    * Saida: True caso a operação tenha funcionado, False caso contrário.
*/
bool desempilhaId(PilhaId *x, int *id){
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
    * Nome: criarPC.
    * Entrada: 1 ponteiro para PilhaChoc.
    * Processo: Caso a PilhaChoc inserida exista, atribui NULL ao ponteiro de Chocolate topo.
*/
void criarPC(PilhaChoc *x){
    x->topo = NULL;
}

/*
    * Nome: destruirPC.
    * Entrada: 1 ponteiro para PilhaChoc.
    * Processo: Caso a Pilha inserida exista, é desalocada.
*/
void destruirPC(PilhaChoc *x){
    if(x != NULL){
        free(x);
    }
}

/*
    * Nome: vaziaPC.
    * Entrada: 1 ponteiro de PilhaChoc.
    * Processo: Verifica se a Pilha está vazia checando se o Chocolate topo é NULL.
    * Saida: True caso o topo seja NULL, False caso contrário.
*/
bool vaziaPC(PilhaChoc *x){
    if(x->topo == NULL){
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: empilhaC.
    * Entrada: 1 ponteiro para Pilha e 1 ponteiro para char com o nome do chocolate.
    * Processo: - Cria um Chocolate;
                - Atribui a ele o ponteiro para char inserido na função e aponta o próximo para 
                  o topo da pilha que, por sua vez, aponta para o Chocolate criado.
    * Saida: True caso a operação tenha funcionado, False caso contrário.
*/
bool empilhaC(PilhaChoc *x, char *nome){
    Chocolate *y = (Chocolate*) malloc(sizeof(Chocolate));
    if(y != NULL){
        strcpy(y->nome, nome);
        y->prox = x->topo;
        x->topo = y;
        return true;
    }else{
        return false;
    }
}


/*
    * Nome: desempilhaC.
    * Entrada: 1 ponteiro para Pilha e 1 ponteiro para char com o nome do chocolate.
    * Processo: - Testa se a Pilha está vazia, se não estiver, cria um ponteiro para Chocolate e aponta ele para o topo da 
                  Pilha;
                - Em seguida, o topo da Pilha vai apontar para o proximo do Chocolate criado, que vai apontar para NULL;
                - Em sequência o ponteiro para char do Chocolate é copiado para o ponteiro para char inserido na função, 
                  e o Chocolate criado é desalocado.
    * Saida: True caso a operação tenha funcionado, False caso contrário.
*/
bool desempilhaC(PilhaChoc *x, char *nome){
    if(!vaziaPC(x)){
        Chocolate *y = x->topo;
        x->topo = y->prox;
        y->prox = NULL;
        strcpy(nome, y->nome);
        free(y);
        return true;
    }else{
        return false;
    }
}

/*
    * Nome: imprimeF.
    * Entrada: 1 ponteiro para Fila, 1 vetor de Itens(cardápio) e 1 ponteiro para PilhaChoc.
    * Processo: - Cria 1 PilhaId;
                - 1 ponteiro para char de 30 posições e 1 int para o id dos itens;
                - Enquanto a Fila não estiver vazia, retira um Cliente armazenando o nome no ponteiro para char
                  criado anteriormente e aponta o topo da pilha criada para a pilha presente no Cliente.
*/
void imprimeF(Fila *x, Item *cardapio, PilhaChoc *pC){
    cabecalho();
    if(vaziaF(x)){
        printf("Fila Vazia.\n");
    }else{
        PilhaId *p = (PilhaId*) malloc(sizeof(PilhaId));
        criarPId(p);
        char *nome = (char*) malloc(30*sizeof(char));
        char *choc = (char*) malloc(30*sizeof(char));
        char *nomecomida = (char*) malloc(30*sizeof(char));
        int id;
        float preco = 0;
        while (!vaziaF(x)){
            retirar(x, nome, p);
            printf("------------------------------------------------------------");
            printf("\nNome do Cliente: %s\nItens:\n\n", nome);
            while(!vaziaPId(p)){
                float precoUnitario;
                desempilhaId(p, &id);
                itemCardapio(id, nomecomida, &precoUnitario, cardapio);
                printf("\t%s - R$%.2f\n", nomecomida, precoUnitario);
                preco += precoUnitario;
            }
            printf("\nPreco total da comanda: %.2f\n", preco);
            desempilhaC(pC, choc);
            printf("Chocolate dado como brinde: %s\n", choc);
            printf("------------------------------------------------------------\n");
            preco = 0;
        }
        free(p);
        free(nome);
        free(choc);
        free(nomecomida);
    }
}

/*
    * Nome: imprimePId.
    * Entrada: 1 ponteiro para Pilha.
    * Processo: Cria um ponteiro para char de 30 posicoes e, enquanto a Pilha nao estiver vazia, desempilha um Elemento 
                e coloca seu valor no ponteiro de char criado e o imprime.
*/
void imprimePId(PilhaId *x){
    int y;
    while (!vaziaPId(x)){
        desempilhaId(x, &y);
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

/*
    * Nome: imprimeCardapio.
    * Entrada: 1 vetor de Itens.
    * Processo: - Recebe a função cabecalho();
                - Dentro de um for imprime as informações de cada item do vetor(cardápio).
*/
 void imprimeCardapio(Item *vetor){
    cabecalho();
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("\t%d. %s - %.2f", vetor[i].id, vetor[i].descricao, vetor[i].preco);
        printf("\n");
    }
    printf("\n");
}

/*
    * Nome: inserirCliente.
    * Entrada: 1 vetor de Itens(cardápio), 1 ponteiro para Fila, 1 ponteiro para PilhaChoc, 1 ponteiro para Chocolate
    * Processo: - Recebe a função cabecalho();
                - Cria 1 PilhaId;
                - 1 vetor de char "nome" com 30 posições para armazenar o nome do cliente inserido temporariamente;
                - 1 vetor de char "choc" com 30 posições para armazenar o nome do chocolate atribuido ao cliente usando 
                  a função "rand()";
                - Imprime o cardápio e seleciona 1 item por vez do cardápio até que a condição de parada seja 
                  satisfeita: ctrl != 1.
*/
void inserirCliente(Item *cardapio, Fila *f, PilhaChoc *pC, Chocolate *vetor){
    cabecalho();
    PilhaId *x = (PilhaId*) malloc(sizeof(PilhaId));
    criarPId(x);
    char *nome = (char*) malloc(30*sizeof(char));
    char *choc = (char*) malloc(30*sizeof(char));
    int id, ctrl = 1;
    printf("Insira seu nome: ");fflush(stdin);
    gets(nome);
    imprimeCardapio(cardapio);
    do{
        printf("Escolhe um item do cardapio: ");
        do{
        scanf(" %d", &id);
        }while (id < 0 && id > 10);
        empilhaId(x, id);
        printf("Mais alguma coisa? 1-Sim | 0-Nao ");
        do{
        scanf(" %d", &ctrl);
        }while(ctrl != 1 && ctrl != 0);
    }while(ctrl != 0);
    inserir(f, nome, x);
    free(x);
    free(nome);
    srand(time(NULL));
    strcpy(choc, vetor[rand()%10].nome);
    empilhaC(pC, choc);
}

/*
    * Nome: itemCardapio.
    * Entrada: 1 int id, 1 ponteiro para char com o nome da comida, 1 ponteiro para float com o preço unitário da comida, 1 vetor de Itens(cardápio).
    * Processo: Dentro de um for, confere se o id do item do cardápio é o mesmo passado na chamada da função,
                caso seja, copia para "nomeComida" a string contida em "cardapio[i].descricao" e atribui para o float "precoUnitario" o valor contido em "cardapio[i].preco".
*/
void itemCardapio(int id, char *nomecomida, float *precoUnitario, Item *cardapio){
    for(int i = 0; i < 10; i++){
        if(cardapio[i].id == id){
            strcpy(nomecomida, cardapio[i].descricao);
            *precoUnitario = cardapio[i].preco;
        }
    }
}

/*
    * Nome: cabecalho.
    * Entrada: Não possui entrada.
    * Processo: Cria um cabeçalho para ser inserido no início das outras funções que limpa a tela com "system("cls")" e printa o nome do restaurante.
*/
void cabecalho(){
    system("cls");
    printf("================================================\n");
    printf("\tRESTAURANTE ALAN TURING\n");
    printf("================================================\n\n");
}

/*
    * Nome: clientesAleatorios.
    * Entrada: 1 ponteiro para Fila, 1 vetor de Itens(cardápio), 1 ponteiro para PilhaChoc, 1 ponteiro para Chocolate, e 1 int qtd.
    * Processo: - Cria uma pilha x de ids e um vetor cl de clientes;
                - Inicializa apenas os nomes dos clientes;
                - Cria um loop que escolhe um indice aleatório para nome do cliente, um id aleatório do cardápio e um número
                  aleatório entre 0 e 1 para decidir se o cliente atual escolhido aleatoriamente continua escolhendo os ids dos
                  produtos ou não. A condição de parada do loop é a variável "qtd", presente na entrada;
                - Ainda dentro do loop, cada cliente criado, junto com a sua pilha de ids, é inserido na fila de clientes para
                  fazer checkout;
                - Após o fim do loop, a memória destinada a pilha x e e o vetor de clientes cl é liberada.- Cria 1 PilhaId;
                - 1 vetor de char "nome" com 30 posições para armazenar o nome do cliente atribuido a ele usando
                - 1 vetor de char "choc" com 30 posições para armazenar o nome do chocolate atribuido ao cliente usando 
                  a função "rand()";
*/
void clientesAleatorios(Fila *f, Item *cardapio, Chocolate *vetor, PilhaChoc *pC, int qtd){
    printf("Os clientes serao gerados em %d segundos, aguarde.\n", qtd);
    PilhaId *x = (PilhaId*) malloc(sizeof(PilhaId));
    Cliente *cl = (Cliente*) malloc(20*sizeof(Cliente));
    criarPId(x);
    char *nome = (char*) malloc(30*sizeof(char));
    char *choc = (char*) malloc(30*sizeof(char));
    int id, ctrl = 1;
    strcpy(cl[0].nome, "Tiago");strcpy(cl[10].nome, "Ana");
    strcpy(cl[1].nome, "Herbert");strcpy(cl[11].nome, "Sebastiao");
    strcpy(cl[2].nome, "Marcella");strcpy(cl[12].nome, "Lucas");
    strcpy(cl[3].nome, "Sofia");strcpy(cl[13].nome, "Ricardo");
    strcpy(cl[4].nome, "Joao");strcpy(cl[14].nome, "Michael");
    strcpy(cl[5].nome, "Carlos");strcpy(cl[15].nome, "Roberta");
    strcpy(cl[6].nome, "Maria");strcpy(cl[16].nome, "Luisa");
    strcpy(cl[7].nome, "Eduarda");strcpy(cl[17].nome, "Luiz");
    strcpy(cl[8].nome, "Eduardo");strcpy(cl[18].nome, "Sheila");
    strcpy(cl[9].nome, "Jose");strcpy(cl[19].nome, "Gabriela");

    srand(time(NULL));
    for(int i = 0; i < qtd; i++){
        strcpy(nome, cl[rand()%20].nome);
        do{
            do{
                id = rand()%10;
            }while (id < 0 && id > 10);
            empilhaId(x, id);
            do{
                ctrl = rand()%1;
            }while(ctrl != 1 && ctrl != 0);
        }while(ctrl != 0);
        inserir(f, nome, x);
        srand(time(NULL));
        strcpy(choc, vetor[rand()%10].nome);
        empilhaC(pC, choc);
        printf(".");
        Sleep(1000);
    }
    free(x);
    free(nome);
    printf("\nClientes gerados com sucesso.\n");
}
