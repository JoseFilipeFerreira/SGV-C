#include "produtos.h"
#include <gmodule.h>

#define MAXPROD 200000
#define MAXBPROD 10

char* produtos[MAXPROD];
GHashTable* productTable;
int productNumber;

void readProducts() {
    int i;
    FILE* f = fopen("./db/Produtos.txt", "r");
    productTable = g_hash_table_new(g_str_hash, g_str_equal);
    char* buff = malloc(MAXBPROD);
    for(i = 0; fgets(buff, MAXBPROD, f); i++) {
        produtos[i] = malloc(MAXBPROD);
        strcpy(produtos[i], strtok(buff, "\n\r"));
    }
    free(buff);
    productNumber = i;
    fclose(f);
}

void verifyProducts() {
    int r, w, id;
    for(r = w = 0; r < productNumber; r++) {
        sscanf(produtos[r], "%*2c%4d%*s", &id);
        if(id >= 1000 && id <= 9999)
            if(g_hash_table_add(productTable, produtos[r]))
                w++;
    }
    productNumber = w;
}

int searchProduct(char* id) {
    return (g_hash_table_contains(productTable,id) != 0L);
}

int getProductNumber() {
    return productNumber;
}

void initProducts() {
    readProducts();
    verifyProducts();
}
