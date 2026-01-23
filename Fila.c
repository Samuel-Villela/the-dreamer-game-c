#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    No *prox;
} No;
typedef struct fila
{
    No *inicio;
    No *fim;
} Fila;

void criar(Fila *f);
int estaVazia(Fila *f);
void inserir(Fila *f, int novoValor);
void retirar(Fila *f, int *valorRemovido);
int front(Fila *f, int *valorDele);

void criar(Fila *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}
int estaVazia(Fila *f)
{
    if (f->inicio == NULL) return 1;
}
void inserir(Fila *f, int novoValor)
{
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL){
        return;
    }
    novo->valor = novoValor;
    novo->prox = NULL;

    if(estaVazia(f)){
        f->inicio = novo;
        f->fim = novo;
    }
    else{
        f->fim->prox = novo;
        f->fim = novo;
    }
    return;
}
void retirar(Fila *f, int *valorRemovido)
{
    if(estaVazia(f)){
        return;
    }
    No *aux = f->inicio;
    *valorRemovido = aux->valor;
    f->inicio = aux->prox;
    
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    free(aux);
}
int front (Fila *f, int *valorDele)
{
    if(estaVazia(f)){
        return 0;
    }
    *valorDele = f->inicio->valor;
    return *valorDele;
}