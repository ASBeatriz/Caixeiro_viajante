#include "pilha.h"

struct pilha
{
    ITEM *item[TAM];
    int tamanho; /*topo da pilha*/
};
    
PILHA *pilha_criar(void){
    
    PILHA *pilha = (PILHA *) malloc(sizeof(PILHA));

    if (pilha != NULL){
        pilha->tamanho = 0;
    }

    return(pilha);
}

bool pilha_vazia(PILHA* pilha){
    if (pilha != NULL){
        return ((pilha->tamanho == 0) ? true : false);
    }
    return(false);
}

bool pilha_cheia(PILHA* pilha){
    if (pilha != NULL){
        return ((pilha->tamanho == TAM) ? true : false);
    }
    return(true);
}

int pilha_tamanho(PILHA *pilha){
    return ((pilha != NULL) ? pilha->tamanho : -1);
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if (!pilha_cheia(pilha)){
        pilha->item[pilha->tamanho] = item;
        pilha->tamanho++;
        return(true);
    } 
    return(false);
}

ITEM *pilha_desempilhar(PILHA *pilha){
    ITEM* i = NULL;
    if (!pilha_vazia(pilha)){
        i = pilha_topo(pilha);
        pilha->item[pilha->tamanho-1] = NULL;
        pilha->tamanho--;
    } 

    return(i);  
}

void pilha_apagar(PILHA **pilha){
    int i, j;

    if (*pilha == NULL){
        return;
    }

    j = pilha_tamanho(*pilha);

    for (i = 0; i < j; i++){
        item_apagar(&((*pilha)->item[i]));
    }

    free(*pilha);
    *pilha = NULL;
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha != NULL){
        return pilha->item[(pilha->tamanho-1)];
    }
    return NULL;
}
