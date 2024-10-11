#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Lista.h"

// Estrutura do nó da lista de adjacência (oculta do usuário do TAD)
struct adjacencia {
    int cidade;            // Índice da cidade adjacente
    int distancia;         // Distância para a cidade adjacente
    struct adjacencia *prox; // Próximo nó na lista
};

// Estrutura para a lista de adjacências (oculta do usuário do TAD)
struct lista {
    Adjacencia *inicio;    // Ponteiro para o início da lista de adjacências
};

// Função para criar a lista de adjacências
LISTA* lista_criar() {
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if (lista != NULL) {
        lista->inicio = NULL;
    }
    return lista;
}

// Função para criar um nó de adjacência
Adjacencia* lista_criar_adjacencia(int cidade, int distancia) {
    Adjacencia *nova = (Adjacencia*) malloc(sizeof(Adjacencia));
    nova->cidade = cidade;
    nova->distancia = distancia;
    nova->prox = NULL;
    return nova;
}

// Função para inserir uma adjacência na lista de uma cidade
void lista_inserir_adjacencia(LISTA *lista, int cidade, int distancia) {
    Adjacencia *nova = lista_criar_adjacencia(cidade, distancia);
    nova->prox = lista->inicio;
    lista->inicio = nova;
}

// Função para liberar a memória de uma lista de adjacências
void lista_apagar(LISTA *lista) {
    Adjacencia *atual = lista->inicio;
    while (atual != NULL) {
        Adjacencia *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

// Função para buscar a distância entre duas cidades
int lista_obter_distancia(LISTA *lista, int cidade) {
    Adjacencia *adj = lista->inicio;
    while (adj != NULL) {
        if (adj->cidade == cidade) {
            return adj->distancia;
        }
        adj = adj->prox;
    }
    return DISTANCIA_MAXIMA; // Retorna infinito se não houver conexão
}

// Função que calcula a distância de um caminho dado
int lista_calcular_distancia(LISTA *listaCidades[], int *permutacao, int n) {
    int distancia_total = 0;

    // Percorre todas as cidades da permutação
    for (int i = 0; i < n - 1; i++) {
        int cidade_atual = permutacao[i];
        int proxima_cidade = permutacao[i + 1];
        
        // Busca a distância entre cidade_atual e proxima_cidade na lista de adjacências
        distancia_total += lista_obter_distancia(listaCidades[cidade_atual], proxima_cidade);
        
        if (distancia_total >= DISTANCIA_MAXIMA) return DISTANCIA_MAXIMA; // Se não encontrar caminho, distância é infinita
    }

    // Volta para a cidade inicial
    int ultima_cidade = permutacao[n - 1];
    int primeira_cidade = permutacao[0];

    distancia_total += lista_obter_distancia(listaCidades[ultima_cidade], primeira_cidade);
    
    if (distancia_total >= DISTANCIA_MAXIMA) return DISTANCIA_MAXIMA; // Se não encontrar caminho, distância é infinita
    return distancia_total;
}