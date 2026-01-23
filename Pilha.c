#include <stdlib.h>
#include <stdio.h>

typedef struct No
{
    int valor;
    No *prox;
} No;
typedef struct Pilha
{
    No *topo;
} Pilha;

void push(Pilha *p,int novoValor);
void pop(Pilha *p, int *valorRemovido);
void criar(Pilha *p);
int estaVazia(Pilha *p);

void criar(Pilha *p)
{
    p->topo = NULL;
}

int estaVazia(Pilha *p)
{
    return(p->topo == NULL);
}

void push(Pilha *p, int novoValor)
{
    No *novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        return;
    }
    novo->valor = novoValor;
    novo->prox = p->topo;
    p->topo = novo;
}
void pop(Pilha *p, int *valorRemovido)
{
    if(estaVazia(p)){
        return;
    }
    No *aux = p->topo;
    *valorRemovido = aux->valor;
    p->topo = aux->prox;
    free(aux);
}