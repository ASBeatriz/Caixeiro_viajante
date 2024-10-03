#include <stdlib.h>
#include <stdio.h>
#include "item.h"

struct item_{
    int cidade1;
    int cidade2; 
    int distancia;
};

ITEM *item_criar (int cidade1, int cidade2, int distancia){
    ITEM *item;

    item = (ITEM *) malloc(sizeof(ITEM));

    if (item != NULL){
        item->cidade1 = cidade1;
        item->cidade2 = cidade2;
        item->distancia = distancia;
        return(item);
    }
    return(NULL);
}

bool item_apagar(ITEM **item){
    if (*item != NULL){
        free(*item);
        *item = NULL;
        return(true);
    }
    return(false);
}

int item_get_cidade1(ITEM *item){
    if (item != NULL){
        return(item->cidade1);
        exit(1);
    }
}

int item_get_cidade2(ITEM *item){
    if (item != NULL){
        return(item->cidade2);
        exit(1);
    }
}

int item_get_distancia(ITEM *item){
    if (item != NULL){
        return(item->distancia);
    }
    exit(1);
}