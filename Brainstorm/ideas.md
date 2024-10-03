A, B, C

CIDADE A:
    inteiro indice = 1

ADJ:
    inteiro indice1
    inteiro indice2 
    inteiro distancia

------------

leitura das distancias
ID1 ID2 DIST
1   2   10


CRIAR ADJ1:
    inteiro indice = 2

LISTA arestas[adj1, adj2, adj3]

QUERO VER CIDADE 1 E CIDADE 2 ESTÃO CONECTADAS


INT VERIFICA_ARESTA(int cidade1, int cidade2)
    PARA i=0 até i=[TAM_LISTA], i++
        SE  ((aresta[i]->indice1 == cidade1 || aresta[i]->indice2 == cidade1) &&  
            (aresta[i]->indice1 == cidade2 || aresta[i]->indice2 == cidade2))
                return aresta[i]->distancia
    
    return -1