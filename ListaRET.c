#include <stdio.h>
#include <stdlib.h>

typedef struct LISTA {
    int tipo; // 1 = retangulo, 2 = circulo, 3 = triangulo
    void *info;
    struct LISTA* prox;
} LISTA;

typedef struct RETANGULO {
    int altura;
    int largura;
} RETANGULO;

typedef struct CIRCULO {
    int raio;
} CIRCULO;

typedef struct TRIANGULO {
    int base;
    int altura;
} TRIANGULO;

// ===== Funções =====
LISTA* inserir(LISTA* lista, int tipo, void* info);
void imprimir(LISTA* lista);
void liberar(LISTA* lista);

// ===== MAIN =====
int main() {
    LISTA* lista = NULL;

    RETANGULO* r = (RETANGULO*)malloc(sizeof(RETANGULO));
    r->altura = 10;
    r->largura = 5;

    CIRCULO* c = (CIRCULO*)malloc(sizeof(CIRCULO));
    c->raio = 7;

    TRIANGULO* t = (TRIANGULO*)malloc(sizeof(TRIANGULO));
    t->base = 6;
    t->altura = 4;

    lista = inserir(lista, 1, r);
    lista = inserir(lista, 2, c);
    lista = inserir(lista, 3, t);

    imprimir(lista);
    liberar(lista);
    return 0;
}

// ===== Implementações =====
LISTA* inserir(LISTA* lista, int tipo, void* info) {
    LISTA* novo = (LISTA*)malloc(sizeof(LISTA));
    novo->tipo = tipo;
    novo->info = info;
    novo->prox = lista;
    return novo;
}

void imprimir(LISTA* lista) {
    LISTA* p = lista;
    while (p != NULL) {
        switch (p->tipo) {
            case 1: {
                RETANGULO* r = (RETANGULO*)p->info;
                printf("Retangulo - altura: %d, largura: %d\n", r->altura, r->largura);
                break;
            }
            case 2: {
                CIRCULO* c = (CIRCULO*)p->info;
                printf("Circulo - raio: %d\n", c->raio);
                break;
            }
            case 3: {
                TRIANGULO* t = (TRIANGULO*)p->info;
                printf("Triangulo - base: %d, altura: %d\n", t->base, t->altura);
                break;
            }
        }
        p = p->prox;
    }
}

void liberar(LISTA* lista) {
    LISTA* p = lista;
    while (p != NULL) {
        LISTA* temp = p->prox;
        free(p->info);
        free(p);
        p = temp;
    }
}
