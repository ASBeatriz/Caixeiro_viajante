#ifndef PILHA_H
    #define PILHA_H
    #define TAM 100

    #include "item.h"
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct pilha PILHA;

    PILHA *pilha_criar(void);
    void pilha_apagar(PILHA **pilha);
    bool pilha_vazia(PILHA *pilha);
    bool pilha_cheia(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    ITEM *pilha_topo(PILHA *pilha);
    bool pilha_empilhar(PILHA *pilha, ITEM *item);
    ITEM *pilha_desempilhar(PILHA *pilha);
    //void pilha_print(PILHA *p);

#endif