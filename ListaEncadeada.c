#include <stdio.h>
#include <stdlib.h>

void inserirInicio(struct LISTA** l_ref, int novoValor);
void inserirFim(struct LISTA** l_ref, int novoValor);
void removerElemento(struct LISTA** l_ref, int valor);
void imprimirLista(struct LISTA* l_ref);

typedef struct LISTA
{
    int valor;
    struct LISTA* prox;
} LISTA;

void inserirInicio(struct LISTA** l_ref, int novoValor)
{
    struct LISTA* novoNo = (struct LISTA*)malloc(sizeof(struct LISTA));
    novoNo->valor = novoValor;
    novoNo->prox = *l_ref;
    *l_ref = novoNo;
}

void inserirFim(struct LISTA** l_ref, int novoValor)
{
    struct LISTA* novoNo = (struct LISTA*)malloc(sizeof(struct LISTA));
    novoNo->valor = novoValor;
    novoNo->prox = NULL;

    LISTA* temp = *l_ref;

    if (*l_ref == NULL){
        *l_ref = novoNo;
        return;
    }

    while (temp->prox != NULL)
    {
        temp = temp->prox;
    }
    temp->prox = novoNo;
}
void removerElemento(struct LISTA** l_ref, int valor)
{
    struct LISTA* temp = *l_ref;
    struct LISTA* anterior = NULL;
    
    if(temp == NULL){
        printf("Lista vazia");
        return;
    }
    if(temp != NULL && temp->valor == valor){
        *l_ref = temp->prox;
        free(temp);
        printf("Elemento removido com sucesso");
        return;
    }
    while(temp != NULL && temp->valor != valor)
    {
        anterior = temp;
        temp = temp->prox;
    }
    if(temp == NULL){
        printf("Elemento nao encontrado");
        return;
    }

    anterior->prox = temp->prox;
    free(temp);
    printf("Elemento removido com sucesso");
}