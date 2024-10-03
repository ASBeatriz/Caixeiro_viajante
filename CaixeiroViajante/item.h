#ifndef ITEM_H
    #define ITEM_H

    #include <stdbool.h>

    typedef struct item_ ITEM;

    ITEM *item_criar (int cidade1, int cidade2, int distancia);
    bool item_apagar (ITEM **item);
    int item_get_chave (ITEM *item);
    bool item_set_chave (ITEM *item, int chave);
    void *item_get_dados (ITEM *item);

#endif