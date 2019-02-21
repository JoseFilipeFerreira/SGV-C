#include "produtos.h"

char* produtos[200000];

int readProducts() {
    int i;
    FILE* f = fopen("./db/Produtos.txt", "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++)
        produtos[i] = strdup(buff);
    return i;
}

int verifyProducts(int n) {
    int r, w, id;
    for(r = w = 0; r < n; r++) {
        sscanf(produtos[r], "%*2c%4d%*s", &id);
        if(id >= 1000 && id <= 9999) 
            produtos[w++] = strdup(produtos[r]);
    }
    return w;
}
