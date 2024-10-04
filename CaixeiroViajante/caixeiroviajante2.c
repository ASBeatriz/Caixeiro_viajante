/*
O que o programa faz até agora:
    - Lê as arestas e cria a lista que as armazenas.
    - A lista está funcional.

Falta:
    - Função para aplicar backtracking para gerar as permutações (com o array IDCidades)
    - Função que utiliza "verificar_aresta" para verificar se o caminho é válido e somar as distâncias
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "Lista_seq.h"

int main(void){
    int numCidades;         // Quantidade de cidades 
    int cidadeInicial;      // Índice da cidade inicial
    int numArestas;         // Quantidade de estradas no mapa
    
    // Lê o número de cidades, cidade inicial e quantidade de arestas
    scanf("%d %d %d", &numCidades, &cidadeInicial, &numArestas);

    // Preenche o vetor de índice de cidades 
    int IDCidades[numCidades];
    for (int i = 0; i < numCidades; i++) {
        IDCidades[i] = i+1;
    }

    // Lista que contém structs com os ids das cidades e suas respectivas distâncias
    LISTA *arestas = lista_criar();
    
    // Leitura das distâncias entre as cidades
    int IDCidade1, IDCidade2, distancia;
    for (int j = 0; j < numArestas; j++)
    {
        scanf("%d %d %d", &IDCidade1, &IDCidade2, &distancia);

        ITEM *it = item_criar(IDCidade1, IDCidade2, distancia);

        lista_inserir(arestas, it);
    }

    lista_imprimir(arestas);    // debug

    return 0;
}