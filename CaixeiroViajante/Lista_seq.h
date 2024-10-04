#ifndef LISTA_SEQ_H
#define LISTA_SEQ_H

#include <stdlib.h>  // para alocação dinâmica
#include <stdio.h>  // para printf
#include "item.h"
#define TAM_MAX 100
#define ERRO -1

typedef struct lista LISTA;

LISTA *lista_criar();
bool lista_inserir(LISTA *lista, ITEM *item);
ITEM *lista_remover(LISTA *lista);
bool lista_apagar(LISTA **lista);

int verifica_aresta(LISTA *arestas, int cidade1, int cidade2);
bool lista_cheia(LISTA *lista);
bool lista_vazia(LISTA *lista);
int lista_tamanho(LISTA *lista);
void lista_imprimir(LISTA* lista);

#endif