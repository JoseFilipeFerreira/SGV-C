#include "produto.h"

struct produto {
    char* id;
};

int verifyProduct(const char* id) {
    char c1, c2;
    int n;
    if(strlen(id) == 6) {
        sscanf(id, "%c%c%d%*s", &c1, &c2, &n);
        return strlen(id) == 6 && c1 <= 'Z' && c1 >='A' && c2 <= 'Z' && c2 >='A' && n >= 1000 && n <= 9999;
    }
    return 0;
}

Produto mkProduct(char* id) {
    char* product = malloc(strlen(id) + 1);
    Produto produto = malloc(sizeof(struct produto));
    strcpy(product, strtok(id, "\n\r"));
    produto->id = product;
    return produto;
}

const char* getIdProduct(Produto produto) {
    return produto->id;
}

void destroyProduct(Produto produto) {
    free(produto->id);
    free(produto);
}
