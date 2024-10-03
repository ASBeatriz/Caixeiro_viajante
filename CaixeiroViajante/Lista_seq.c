#include "Lista_seq.h"

struct lista{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim;
    int tamanho;
    bool ordenada;
};

/* --------------------- FUNÇÕES AUXILIARES DAS FUNÇÕES ----------------------- */

// achar a posição do menor número n, tal que seja maior ou igual ao indicado (chave)
int lower_bound(LISTA *lista, int chave){
    int meio, ini = lista->inicio, fim = lista->fim, ans = -1;
    while(ini <= fim){
        meio = (ini+fim)/2;
        if(item_get_chave(lista->itens[meio]) >= chave){
            ans = meio;
            fim = meio - 1;
        }
        else{
            ini = meio + 1;
        }
    }
    return ans; //caso de não achar
}

//desloca parte da lista para a direita, deixando a posição pos livre
void deslocar_dir(LISTA *lista, int pos){ 
    // só desloco caso seja uma posição ocupada
    if(pos > lista->fim) return;

    for(int i = lista->fim+1; i>pos; i--){
        lista->itens[i] = lista->itens[i-1];
    }
}

/*  Desloca parte da lista para a esquerda (a partir de pos+1). Usada quando um item é apagado. */
void deslocar_esq(LISTA *lista, int pos){ 

    //só desloco se houver elementos após a posição indicada
    if(pos >= lista->fim) return;

    for(int i=pos; i<lista->fim; i++){
        if(i == lista->fim){
            lista->itens[i] = NULL;
            break;
        }
        lista->itens[i] = lista->itens[i+1];    // cada posição recebe o valor do próx, exceto pelo último
    }
}

bool inserir_posicao(LISTA *lista, ITEM *item, int pos){
    if(lista != NULL && !lista_cheia(lista)){
        if(pos <= (lista->fim) + 1){      //se a posição estiver na lista ou for após o último elemento
            deslocar_dir(lista, pos);
            lista->itens[pos] = item;
            if(lista->tamanho != 0) lista->fim++;   //só incrementa o fim se não for o primeiro elemento
            lista->tamanho++;
            return true;
        }
    }
    return false;
}
/* -------------------------------------------------------------- */

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }
    return lista;
}

bool inserir_nao_ordenado(LISTA *lista, ITEM *item){
    if(lista != NULL && !lista_cheia(lista)){
        int pos;

        //se for o primeiro item
        if(lista->tamanho == 0) pos = 0;    
        else pos = (lista->fim) + 1;

        inserir_posicao(lista, item, pos);
        return true;
    }
    return false;
}

bool inserir_ordenado(LISTA *lista, ITEM *item){ //ordenado por chave
    int chave = item_get_chave(item);
    if(lista != NULL && !lista_cheia(lista)){
        int pos;
        // caso em que a lista está vazia
        if(lista->tamanho == 0) pos = 0;
        else {
            pos = lower_bound(lista, chave);

            //caso em que o item inserido é maior que todos
            if(pos == -1) pos = lista->fim + 1;
        }

        return inserir_posicao(lista, item, pos);
    }
    return false;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    return (lista->ordenada ? inserir_ordenado(lista, item) : inserir_nao_ordenado(lista, item));
}


ITEM *lista_remover(LISTA *lista, int chave){ 
    if(lista != NULL && !lista_vazia(lista)){
        ITEM *removido;
        int pos;

        //se for ordenada, faz busca binária (lower bound)
        if(lista->ordenada){
            pos = lower_bound(lista, chave);
            if(pos == -1 || chave != item_get_chave(lista->itens[pos])) return NULL;   // se não achar o item
        }
        //senão, percorre a lista procurando a chave correspondente
        else{
            for(pos = lista->inicio; pos < lista->tamanho; pos++){
                if(item_get_chave(lista->itens[pos]) == chave){
                    break;
                }
                //se estiver na ultima incrementação do for e não tiver achado o item
                if(pos + 1 == lista->tamanho) return NULL;  
            }
        }

        removido = lista->itens[pos];
        deslocar_esq(lista, pos);
        lista->tamanho--;
        lista->fim--;
        return removido;

    }
    return NULL;
}

ITEM *lista_busca(LISTA *lista, int chave){
    // se for ordenada, utiliza busca binária (lower bound)
    if(lista->ordenada){
        int pos = lower_bound(lista, chave); 
        if(pos == -1 || item_get_chave(lista->itens[pos]) != chave) 
            return NULL;

        printf("chave %d na posição: %d\n", chave, pos);
        return lista->itens[pos];
    }
    // senão, percorre a lista até achar
    else{
        if(lista != NULL){
            for(int pos = lista->inicio; pos < lista->tamanho; pos++){
                if(item_get_chave(lista->itens[pos]) == chave){
                    printf("chave %d na posição: %d\n", chave, pos);
                    return lista->itens[pos];
                }
            }
        }
        return NULL;
    }
}

bool lista_apagar(LISTA **lista){ 
    if(*lista == NULL) return true;

    while((*lista)->tamanho != 0){
        ITEM *removido = lista_remover(*lista, item_get_chave((*lista)->itens[(*lista)->fim]));
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
            int pos = lista->inicio;
            for(int i=0; i<lista->tamanho; i++){
                int val = *(int *)item_get_dados(lista->itens[pos]);
                printf("%d ", val);
                pos++;
            }
            printf("\n");
        }
    }
}

