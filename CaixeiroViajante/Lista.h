#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>  // para alocação dinâmica

// Define uma constante para a maior distância possível (representa "infinito")
#define DISTANCIA_MAXIMA 100000

typedef struct adjacencia Adjacencia;
typedef struct lista LISTA;

// Funções públicas do TAD Lista Encadeada
LISTA* lista_criar();
void lista_inserir_adjacencia(LISTA *lista, int cidade, int distancia);
void lista_apagar(LISTA *lista);
int lista_calcular_distancia(LISTA *listaCidades[], int *permutacao, int n);
int lista_obter_distancia(LISTA *lista, int cidade);

#endif