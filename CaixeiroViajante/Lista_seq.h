#ifndef LISTA_SEQ_H
#define LISTA_SEQ_H

#include "item.h"
#define TAM_MAX 100
#define ERRO -1

typedef struct lista LISTA;

LISTA *lista_criar(bool ordenada);
bool lista_inserir(LISTA *lista, ITEM *item);
ITEM *lista_remover(LISTA *lista, int chave);
ITEM *lista_busca(LISTA *lista, int chave);
bool lista_apagar(LISTA **lista);

bool lista_cheia(LISTA *lista);
bool lista_vazia(LISTA *lista);
int lista_tamanho(LISTA *lista);
void lista_imprimir(LISTA* lista);

#endif