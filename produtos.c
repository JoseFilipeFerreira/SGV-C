#include "produtos.h"
#include <gmodule.h>

char* produtos[200000];
GHashTable* productTable;
int productNumber;

void readProducts() {
    int i;
    FILE* f = fopen("./db/Produtos.txt", "r");
    productTable = g_hash_table_new(g_str_hash, g_str_equal);
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++) {
        buff[6] = '\0';
        produtos[i] = malloc(10);
        strcpy(produtos[i], buff);
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
