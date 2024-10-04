#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Lista_seq.h"

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
LISTA* cria_lista() {
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if (lista != NULL) {
        lista->inicio = NULL;
    }
    return lista;
}

// Função para criar um nó de adjacência
Adjacencia* cria_adjacencia(int cidade, int distancia) {
    Adjacencia *nova = (Adjacencia*) malloc(sizeof(Adjacencia));
    nova->cidade = cidade;
    nova->distancia = distancia;
    nova->prox = NULL;
    return nova;
}

// Função para inserir uma adjacência na lista de uma cidade
void insere_adjacencia(LISTA *lista, int cidade, int distancia) {
    Adjacencia *nova = cria_adjacencia(cidade, distancia);
    nova->prox = lista->inicio;
    lista->inicio = nova;
}

// Função para liberar a memória de uma lista de adjacências
void libera_lista(LISTA *lista) {
    Adjacencia *atual = lista->inicio;
    while (atual != NULL) {
        Adjacencia *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

// Função que calcula a distância de um caminho dado
int calcula_distancia(LISTA *listaCidades[], int *permutacao, int n) {
    int distancia_total = 0;

    // Percorre todas as cidades da permutação
    for (int i = 0; i < n - 1; i++) {
        int cidade_atual = permutacao[i];
        int proxima_cidade = permutacao[i + 1];
        
        // Busca a distância entre cidade_atual e proxima_cidade na lista de adjacências
        Adjacencia *adj = listaCidades[cidade_atual]->inicio;
        int distancia_encontrada = 0;
        while (adj != NULL) {
            if (adj->cidade == proxima_cidade) {
                distancia_total += adj->distancia;
                distancia_encontrada = 1;
                break;
            }
            adj = adj->prox;
        }
        
        if (!distancia_encontrada) return INT_MAX; // Se não encontrar caminho, distância é infinita
    }

    // Volta para a cidade inicial
    int ultima_cidade = permutacao[n - 1];
    int primeira_cidade = permutacao[0];
    Adjacencia *adj = listaCidades[ultima_cidade]->inicio;
    int distancia_encontrada = 0;
    while (adj != NULL) {
        if (adj->cidade == primeira_cidade) {
            distancia_total += adj->distancia;
            distancia_encontrada = 1;
            break;
        }
        adj = adj->prox;
    }
    
    if (!distancia_encontrada) return INT_MAX; // Se não encontrar caminho, distância é infinita
    return distancia_total;
}