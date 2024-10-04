#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Lista_seq.h"

// Define uma constante para a maior distância possível (representa "infinito")
#define DISTANCIA_MAXIMA 10000

// Função que troca dois elementos de um array
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função que gera todas as permutações usando backtracking
void permutacao(LISTA *listaCidades[], int *cidades, int l, int r, int n, int *melhor_caminho, int *menor_distancia)
{
    if (l == r)
    {
        // Calcula a distância total para a permutação atual
        int distancia_atual = calcula_distancia(listaCidades, cidades, n);
        if (distancia_atual < *menor_distancia)
        {
            *menor_distancia = distancia_atual;
            for (int i = 0; i < n; i++)
            {
                melhor_caminho[i] = cidades[i]; // Armazena o melhor caminho
            }
        }
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            troca(&cidades[l], &cidades[i]);
            permutacao(listaCidades, cidades, l + 1, r, n, melhor_caminho, menor_distancia);
            troca(&cidades[l], &cidades[i]); // Backtrack
        }
    }
}

int main(void)
{
    int numCidades;    // Quantidade de cidades
    int cidadeInicial; // Índice da cidade inicial
    int numArestas;    // Quantidade de estradas no mapa

    // Lê o número de cidades, cidade inicial e quantidade de arestas
    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);

    // Preenche o vetor de índice de cidades
    int IDCidades[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        IDCidades[i] = i; // Índices de cidades começam em 0
    }

    // Cria a lista de adjacências para cada cidade
    LISTA *listaCidades[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        listaCidades[i] = cria_lista();
    }

    // Leitura das distâncias entre as cidades
    int IDCidade1, IDCidade2, distancia;
    for (int j = 0; j < numArestas; j++)
    {
        scanf("%d %d %d", &IDCidade1, &IDCidade2, &distancia);
        insere_adjacencia(listaCidades[IDCidade1 - 1], IDCidade2 - 1, distancia); // Ajusta para índice 0
        insere_adjacencia(listaCidades[IDCidade2 - 1], IDCidade1 - 1, distancia); // Para grafo não direcionado
    }

    // Variáveis para armazenar o melhor caminho e a menor distância
    int melhor_caminho[numCidades];
    int menor_distancia = DISTANCIA_MAXIMA;

    // Chama a função de permutação
    permutacao(listaCidades, IDCidades, 0, numCidades - 1, numCidades, melhor_caminho, &menor_distancia);

    // Imprime o menor caminho e a menor distância
    printf("Menor distancia: %d\n", menor_distancia);
    printf("Melhor caminho: ");
    for (int i = 0; i < numCidades; i++)
    {
        printf("%d ", melhor_caminho[i] + 1); // Adiciona 1 para imprimir índices começando em 1
    }
    printf("\n");

    // Libera a memória alocada para as listas
    for (int i = 0; i < numCidades; i++)
    {
        libera_lista(listaCidades[i]);
    }

    return 0;
}