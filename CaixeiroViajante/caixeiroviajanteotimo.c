#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "Lista_seq.h"
#include "item.h"

#define DISTANCIA_MAXIMA 10000

// Função que troca dois elementos de um array
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função que gera o Branch and Bound
void branch_and_bound(LISTA *listaCidades[], int *cidades, int n, int nivel, int distancia_atual, int *menor_distancia, int *melhor_caminho, bool visitado[])
{
    if (nivel == n)
    {
        // Adiciona a volta para a cidade inicial
        int ultima_cidade = cidades[n - 1];
        int primeira_cidade = cidades[0];
        int distancia_final = obter_distancia(listaCidades[ultima_cidade], primeira_cidade);

        if (distancia_final != DISTANCIA_MAXIMA)
        {
            distancia_atual += distancia_final;
            if (distancia_atual < *menor_distancia)
            {
                *menor_distancia = distancia_atual;
                for (int i = 0; i < n; i++)
                {
                    melhor_caminho[i] = cidades[i];
                }
            }
        }
        return;
    }

    // Explora todos os caminhos possíveis
    for (int i = 1; i < n; i++)
    {
        if (!visitado[i])
        {
            visitado[i] = true;
            cidades[nivel] = i;

            // Calcula a nova distância para a próxima cidade
            int nova_distancia = distancia_atual + obter_distancia(listaCidades[cidades[nivel - 1]], i);
            if (nova_distancia < *menor_distancia)
            {
                branch_and_bound(listaCidades, cidades, n, nivel + 1, nova_distancia, menor_distancia, melhor_caminho, visitado);
            }

            visitado[i] = false; // Backtrack
        }
    }
}

int main(void)
{
    int numCidades, cidadeInicial, numArestas;

    // Lê o número de cidades, cidade inicial e quantidade de arestas
    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);

    int IDCidades[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        IDCidades[i] = i;
    }

    // Coloca a cidade inicial no primeiro índice
    troca(&IDCidades[0], &IDCidades[cidadeInicial - 1]);

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
        insere_adjacencia(listaCidades[IDCidade1 - 1], IDCidade2 - 1, distancia);
        insere_adjacencia(listaCidades[IDCidade2 - 1], IDCidade1 - 1, distancia); // Para grafo não direcionado
    }

    // Variáveis para armazenar o melhor caminho e a menor distância
    int melhor_caminho[numCidades];
    int menor_distancia = DISTANCIA_MAXIMA;
    bool visitado[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        visitado[i] = false;
    }
    visitado[0] = true; // Cidade inicial já está visitada

    // Captura o tempo de início da execução
    clock_t inicio = clock();

    // Chama o algoritmo Branch and Bound a partir da segunda cidade
    branch_and_bound(listaCidades, IDCidades, numCidades, 1, 0, &menor_distancia, melhor_caminho, visitado);

    // Captura o tempo de fim da execução
    clock_t fim = clock();

    // Calcula o tempo gasto
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Imprime o menor caminho e a menor distância
    printf("Menor distancia: %d\n", menor_distancia);
    printf("Melhor caminho: ");
    for (int i = 0; i < numCidades; i++)
    {
        printf("%d ", melhor_caminho[i] + 1); // Adiciona 1 para imprimir índices começando em 1
    }
    printf("%d\n", melhor_caminho[0] + 1);

    // Imprime o tempo de execução
    printf("Tempo de execucao: %f segundos\n", tempo_gasto);

    // Libera a memória alocada para as listas
    for (int i = 0; i < numCidades; i++)
    {
        libera_lista(listaCidades[i]);
    }

    return 0;
}