#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "Lista.h"

/*
    Função que aplica o algoritmo Branch and Bound.
    Parâmetros:
        - listaCidades: vetor de listas de adjacências das cidades
        - cidades: vetor com as cidades do percurso (exceto a inicial)
        - n: número total de cidades
        - nivel: posição atual no percurso
        - distancia_atual: distância acumulada até o momento
        - menor_distancia: menor distância encontrada até agora
        - melhor_caminho: vetor que armazena o melhor caminho encontrado
        - visitado: vetor auxiliar para indicar se uma cidade foi visitada
        - cidadeInicial: cidade de origem
    Funcionamento:
        A função constrói o percurso a partir da segunda cidade até a penúltima. Em cada nível, para cada 
        cidade não visitada, calcula a distância com a anterior. Se a distância não ultrapassar a menor 
        encontrada, a função é chamada recursivamente para o próximo nível. Quando todas as cidades são 
        visitadas, verifica se o caminho é melhor que o atual e o atualiza, se necessário.
*/
void branch_and_bound(LISTA *listaCidades[], int *cidades, int n, int nivel, int distancia_atual, int *menor_distancia, int *melhor_caminho, bool visitado[], int cidadeInicial)
{
    // Caso em que todas as cidades foram adicionadas
    if (nivel == n-1)
    {
        int ultima_cidade = cidades[n - 2];
        distancia_atual += lista_obter_distancia(listaCidades[ultima_cidade], cidadeInicial);

        if (distancia_atual < *menor_distancia)
        {
            *menor_distancia = distancia_atual;
            for (int i = 0; i < n-1; i++)
            {
                melhor_caminho[i] = cidades[i];
            }
        }
        return;
    }
    // loop para identificar as cidades que ainda não foram adicionadas
    for (int i = 0; i < n; i++)
    {
        if (!visitado[i])
        {
            visitado[i] = true;
            cidades[nivel] = i;

            int cidade_anterior = (nivel == 0)? cidadeInicial : cidades[nivel - 1]; 
            int nova_distancia = distancia_atual + lista_obter_distancia(listaCidades[cidade_anterior], i);

            if (nova_distancia < *menor_distancia)
            {
                branch_and_bound(listaCidades, cidades, n, nivel + 1, nova_distancia, menor_distancia, melhor_caminho, visitado, cidadeInicial);
            }

            visitado[i] = false; // Backtracking
        }
    }
}

/*
    Função principal que lê os dados de entrada, inicializa as estruturas de dados, 
    executa o algoritmo Branch and Bound e imprime o resultado.
*/
int main(void)
{
    int numCidades, cidadeInicial, numArestas;

    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);

    // Preenche o vetor com as identificações das cidades
    int IDCidades[numCidades - 1];
    int posArray = 0;
    for (int i = 0; i < numCidades; i++)
    {
        if(i != (cidadeInicial - 1)){
            IDCidades[posArray] = i; // Pula a cidade inicial
            posArray++;
        }
    }

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
        lista_inserir_adjacencia(listaCidades[IDCidade1 - 1], IDCidade2 - 1, distancia);
        lista_inserir_adjacencia(listaCidades[IDCidade2 - 1], IDCidade1 - 1, distancia); // Para grafo não direcionado
    }

    // Marca as cidades como não visitada inicialmente, exceto a inicial
    bool visitado[numCidades];
    for (int i = 0; i < numCidades; i++)
    {
        visitado[i] = false;
    }
    visitado[cidadeInicial - 1] = true;
    
    // Variáveis para armazenar a solução
    int melhor_caminho[numCidades];
    int menor_distancia = DISTANCIA_MAXIMA;

    // Captura o tempo de início da execução
    clock_t inicio = clock();

    // Chama o algoritmo Branch and Bound
    branch_and_bound(listaCidades, IDCidades, numCidades, 0, 0, &menor_distancia, melhor_caminho, visitado, cidadeInicial-1);

    // Captura o tempo de fim da execução
    clock_t fim = clock();

    // Calcula o tempo gasto
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Imprime o menor caminho, a menor distância e o tempo de execução
    printf("Menor distancia: %d\n", menor_distancia);
    printf("Melhor caminho: ");
    printf("%d ", cidadeInicial);
    for (int i = 0; i < numCidades-1; i++)
    {
        printf("%d ", melhor_caminho[i] + 1); // Adiciona 1, pois os índices começam em 0
    }
    printf("%d\n", cidadeInicial);

    printf("Tempo de execucao: %f segundos\n", tempo_gasto);

    // Libera a memória alocada para as listas
    for (int i = 0; i < numCidades; i++)
    {
        lista_apagar(listaCidades[i]);
    }

    return 0;
}