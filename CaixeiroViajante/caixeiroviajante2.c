#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "Lista_seq.h"

/*
INT VERIFICA_ARESTA(int cidade1, int cidade2)
    PARA i=0 até i=[TAM_LISTA], i++
        SE  ((aresta[i]->indice1 == cidade1 || aresta[i]->indice2 == cidade1) &&  
            (aresta[i]->indice1 == cidade2 || aresta[i]->indice2 == cidade2))
                return aresta[i]->distancia
    
    return -1
*/

int verifica_aresta(LISTA *arestas, int cidade1, int cidade2){
    int tamanho = lista_tamanho(arestas);
    // percorre todas as arestas até achar a aresta das cidades informadas
    for(int i; i<tamanho; i++){
        if(arestas->itens[i])
    }

    return -1;
}

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
    LISTA *arestas = lista_criar(false);
    
    // Leitura das distâncias entre as cidades
    int IDCidade1, IDCidade2, distancia;
    for (int j = 0; j < numArestas; j++)
    {
        scanf("%d %d %d", &IDCidade1, &IDCidade2, distancia);

        ITEM *it = item_criar(IDCidade1, IDCidade2, distancia);

        lista_inserir(arestas, it);
    }
    return 0;
}