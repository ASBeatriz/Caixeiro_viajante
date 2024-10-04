#ifndef ITEM_H
    #define ITEM_H

    #include <stdbool.h>

    typedef struct item_ ITEM;

    ITEM *item_criar (int cidade1, int cidade2, int distancia);
    bool item_apagar (ITEM **item);
    int item_get_cidade1 (ITEM *item);
    int item_get_cidade2 (ITEM *item);
    int item_get_distancia (ITEM *item);

#endif