#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "pilha.h"

typedef struct {
    int melhorRota[12];
    int melhorCusto;
} SOLUCAO;

typedef struct {
    int nome;
    int* distancia;
} CIDADE;

SOLUCAO caixeiroViajante(){
    
}

int calcularCusto (ITEM** rota, int** matrizDistancia)
{
    int custo = 0;

    for (int i = 0; i < sizeof(rota) - 1; i++)
    {
        int cidadeA = item_get_chave(rota[i]);              // Coleta a legenda da cidade A
        int cidadeB = item_get_chave(rota[i+1]);            // Coleta a legenda da cidade B
        int* distancia = (int *) item_get_dados(rota[i]);   // Coleta a distancia entre as cidades
        custo += distancia[cidadeB];
    }
    
    return custo;
}

int main(){
    int numCidades;         // Quantidade de cidades 
    int cidadeInicial;      // Índice da cidade inicial
    int numArestas;         // Quantidade de estradas no mapa
    ITEM *itensCidades[12]; // Vetor de Itens que armazena as cidades
    CIDADE orgCidades[12];  // Vetor de organização dos dados das cidades
    
    // Lê o número de cidades, cidade inicial e quantidade de arestas
    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);
    
    // Aloca e inicializa as distâncias das cidades como 0
    for (int i = 0; i < numCidades; i++)
        orgCidades[i].distancia = (int *)calloc(numCidades, sizeof(int));
    
    // Atribui as distancias entre as cidades
    for (int i = 0; i < numArestas; i++) {
        int cidadeA, cidadeB, distanciaAB;
        scanf("%d %d %d", &cidadeA, &cidadeB, &distanciaAB);
            
        orgCidades[cidadeA - 1].distancia[cidadeB - 1] = distanciaAB;
        orgCidades[cidadeB - 1].distancia[cidadeA - 1] = distanciaAB;
    }

    for (int i = 0; i < numArestas; i++)
        itensCidades[i] = item_criar(i + 1, orgCidades[i].distancia);

    for (int i = 0; i < numCidades; i++){
        printf("cidade %d = %d\n", i+1, item_get_chave(itensCidades[i]));
    }
    
    return 0;
}

/*
1ª linha: O número de cidades (nós) a serem visitadas no mapa (grafo).
● 2ª linha: A cidade inicial (e final) do trajeto.
● 3ª linha: A quantidade de estradas (arestas) existentes no mapa (grafo).
● 4ª linha até o final do arquivo: Pares de cidades e a distância entre elas com
os valores separados por um espaço em branco, com o número linhas de
distância sendo equivalente ao valor da 3ª linha.
*/