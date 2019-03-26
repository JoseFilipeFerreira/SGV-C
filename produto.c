#include "produto.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
@brief Struct para representar a informação de um produto
*/
struct produto {
    char* id; /**< ID do Produto*/
    bool comprou[3];
};

bool verifyProduct(const char* id) {
    char c1, c2;
    int n;
    if(id && strlen(id) == 6) {
        sscanf(id, "%c%c%d%*s", &c1, &c2, &n);
        return c1 <= 'Z' && c1 >='A' && c2 <= 'Z' && c2 >='A' && n >= 1000 && n <= 9999;
    }
    return false;
}

Produto mkProduct(char* id) {
    char* product = malloc(strlen(id) + 1);
    Produto produto = malloc(sizeof(struct produto));
    memset(produto->comprou, 0, sizeof(bool) * 3);
    strcpy(product, strtok(id, "\n\r"));
    produto->id = product;
    return produto;
}

char* getIdProduct(Produto produto) {
    char* r = malloc(strlen(produto->id) + 1);
    strcpy(r, produto->id);
    return r;
}

void updateCompra(Produto p, int filial) {
    p->comprou[filial] = 1;
}

bool foiCompradoOnde(int filial, Produto p) {
    return p->comprou[filial];
}

void destroyProduct(void* pr) {
    Produto produto = (Produto) pr;
    free(produto->id);
    free(produto);
}
