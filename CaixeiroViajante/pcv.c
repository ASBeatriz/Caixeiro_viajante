#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Lista.h"

// Função que troca dois elementos de um vetor
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
    Função que gera todas as permutações usando backtracking.
    Parâmetros:
        - listaCidades: vetor de listas de adjacências das cidades
        - cidades: vetor com as cidades do percurso (exceto a inicial)
        - l: indica a posição atual onde se realiza as trocas (posição da cidade no trajeto)
        - r: indica a posição final 
        - n: número total de cidades
        - menor_distancia: menor distância encontrada até agora
        - melhor_caminho: vetor que armazena o melhor caminho encontrado
    Funcionamento:
    O algoritmo funciona trocando elementos no vetor cidades, criando assim novas sequências. A troca é feita 
    o elemento de uma posição com todos os próximos elementos. Para cada troca, a função é chamada resursivamente
    incrementando o valor de l, até que seja igual a r, ou seja, tenha adicionado todas as cidades. Para cada 
    permutação completa, a distância total do percurso é avaliada e, se o melhor caminho, a solução é atualizada.
*/ 
void permutacao(LISTA *listaCidades[], int *cidades, int l, int r, int n, int *melhor_caminho, int *menor_distancia)
{
    if (l == r)
    {
        // Calcula a distância total para a permutação atual
        int distancia_atual = lista_calcular_distancia(listaCidades, cidades, n);
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

/*
    Função principal que lê os dados de entrada, inicializa as estruturas de dados,
    executa o algoritmo de força bruta e imprime o resultado.
*/
int main(void)
{
    int numCidades, cidadeInicial, numArestas;    

    // Lê o número de cidades, cidade inicial e quantidade de estradas
    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);

    // Preenche o vetor de índice de cidades
    int IDCidades[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        IDCidades[i] = i; // Índices de cidades começam em 0
    }

    // Coloca a cidade inicial no primeiro índice
    troca(&IDCidades[0], &IDCidades[cidadeInicial - 1]);

    // Cria a lista de adjacências para cada cidade
    LISTA *listaCidades[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        listaCidades[i] = lista_criar();
    }

    // Leitura das distâncias entre as cidades
    int IDCidade1, IDCidade2, distancia;
    for (int j = 0; j < numArestas; j++)
    {
        scanf("%d %d %d", &IDCidade1, &IDCidade2, &distancia);
        lista_inserir_adjacencia(listaCidades[IDCidade1 - 1], IDCidade2 - 1, distancia); // Ajusta para índice 0
        lista_inserir_adjacencia(listaCidades[IDCidade2 - 1], IDCidade1 - 1, distancia); // Para grafo não direcionado
    }

    // Variáveis para armazenar a solução
    int melhor_caminho[numCidades];
    int menor_distancia = DISTANCIA_MAXIMA;

    // Chama a função de permutação a partir da segunda cidade
    clock_t inicio = clock();
    permutacao(listaCidades, IDCidades, 1, numCidades - 1, numCidades, melhor_caminho, &menor_distancia);
    clock_t fim = clock();

    // Imprime a solução
    printf("Menor distancia: %d\n", menor_distancia);
    printf("Melhor caminho: ");
    for (int i = 0; i < numCidades; i++)
    {
        printf("%d ", melhor_caminho[i] + 1); // Adiciona 1, pois os índices começam em 0
    }
    // Adiciona a cidade inicial ao final para fechar o ciclo
    printf("%d\n", melhor_caminho[0] + 1);

    // Imprime o tempo de execução
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", tempo_gasto);

    // Libera a memória alocada para as listas
    for (int i = 0; i < numCidades; i++)
    {
        lista_apagar(listaCidades[i]);
    }

    return 0;
}