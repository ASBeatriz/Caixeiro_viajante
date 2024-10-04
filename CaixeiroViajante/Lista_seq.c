#include "Lista_seq.h"

struct lista{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim;
    int tamanho;
};

LISTA *lista_criar(){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        lista->tamanho = 0;
    }
    return lista;
}

// bool inserir_posicao(LISTA *lista, ITEM *item, int pos){
//     if(lista != NULL && !lista_cheia(lista)){
//         if(pos <= (lista->fim) + 1){      //se a posição estiver na lista ou for após o último elemento
//             deslocar_dir(lista, pos);
//             lista->itens[pos] = item;
//             if(lista->tamanho != 0) lista->fim++;   //só incrementa o fim se não for o primeiro elemento
//             lista->tamanho++;
//             return true;
//         }
//     }
//     return false;
// }

bool lista_inserir(LISTA *lista, ITEM *item){   // inserir não ordenado
    if(lista != NULL && !lista_cheia(lista)){
        int pos;

        //se for o primeiro item
        if(lista->tamanho == 0){
            lista->itens[lista->inicio] = item;
        }  
        else{
            lista->fim++;   //só incrementa o fim se não for o primeiro elemento
            lista->itens[lista->fim] = item;
        }
        lista->tamanho++;
    
        return true;
    }
    return false;
}

// Remove o item do ifm
ITEM *lista_remover(LISTA *lista){ 
    if(lista != NULL && !lista_vazia(lista)){
        ITEM *removido = lista->itens[lista->fim];
        lista->tamanho--;
        lista->fim--;
        return removido;
    }
    return NULL;
}


/* Verifica_aresta já faz o trabalho de lista_busca */
// ITEM *lista_busca(LISTA *lista, int chave){
//     if(lista != NULL){
//         for(int pos = lista->inicio; pos < lista->tamanho; pos++){
//             if(item_get_chave(lista->itens[pos]) == chave){
//                 printf("chave %d na posição: %d\n", chave, pos);
//                 return lista->itens[pos];
//             }
//         }
//     }
//     return NULL;
// }

bool lista_apagar(LISTA **lista){ 
    if(*lista == NULL) return true;

    while((*lista)->tamanho != 0){
        ITEM *removido = lista_remover(*lista);
        item_apagar(&removido);
    }
    free(*lista);
    *lista = NULL;
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        return (lista->tamanho == TAM_MAX);
    }
    return true;
}

bool lista_vazia(LISTA *lista){
    if(lista != NULL){
        return (lista->tamanho == 0);
    }
    return false;
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL){
        return lista->tamanho;
    }
    return ERRO;
}

void lista_imprimir(LISTA* lista){
    if(lista != NULL){
        if(lista_vazia(lista)) printf("lista vazia!\n");
        else{
            printf("Arestas: \n");
            for(int pos = lista->inicio; pos < lista->tamanho; pos++){
                int c1 = item_get_cidade1(lista->itens[pos]);
                int c2 = item_get_cidade2(lista->itens[pos]);
                int dist = item_get_distancia(lista->itens[pos]);
                printf("C1: %d C2: %d dist: %d\n", c1, c2, dist);
            }
            printf("\n");
        }
    }
}

/*
INT VERIFICA_ARESTA(int cidade1, int cidade2)
    PARA i=0 até i=[TAM_LISTA], i++
        SE  ((aresta[i]->indice1 == cidade1 || aresta[i]->indice2 == cidade1) &&  
            (aresta[i]->indice1 == cidade2 || aresta[i]->indice2 == cidade2))
                return aresta[i]->distancia
    
    return -1
*/

int verifica_aresta(LISTA *arestas, int cidade1, int cidade2){
    int tamanho = arestas->tamanho;
    // percorre todas as arestas até achar a aresta das cidades informadas
    for(int i; i<tamanho; i++){
        int indice1 = item_get_cidade1(arestas->itens[i]);
        int indice2 = item_get_cidade2(arestas->itens[i]);
        if(((indice1 == cidade1) || (indice2 == cidade1)) && ((indice1 == cidade2) || (indice2 == cidade2))){
            return item_get_distancia(arestas->itens[i]);
        }
    }
    return -1;  // caso não haja caminho entre as cidades   
}