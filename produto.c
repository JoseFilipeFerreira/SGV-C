#include "produto.h"

struct produto {
    char* id;
    int quant[3][12];
    int factP[3][12];
    int factN[3][12];
};

int verifyProduct(const char* id) {
    char c1, c2;
    int n;
    sscanf(id, "%c%c%d%*s", &c1, &c2, &n);
    return strlen(id) == 6 && c1 <= 'Z' && c1 >='A' && c2 <= 'Z' && c2 >='A' && n >= 1000 && n <= 9999;
}

Produto mkProduct(char* id) {
    char* product = malloc(strlen(id) + 1);
    Produto produto = malloc(sizeof(struct produto));
    strcpy(product, strtok(id, "\n\r"));
    produto->id = product;
    memset(produto->quant, 0, sizeof(int)*3*12);
    memset(produto->factN, 0, sizeof(int)*3*12);
    memset(produto->factP, 0, sizeof(int)*3*12);
    return produto;
}

void addQuantProduct(Produto produto, int filial, int mes, int quant) {
    produto->quant[filial - 1][mes - 1] += quant;
}

void addFactProduct(Produto produto, int filial, int mes, int preco, char tipo) {
    if(tipo == 'P') produto->factP[filial - 1][mes - 1] += preco;
    else produto->factN[filial - 1][mes - 1] += preco;
}

const char* getIdProduct(Produto produto) {
    return produto->id;
}

void destroyProduct(Produto produto) {
    free(produto->id);
    free(produto);
}

void printProduct(Produto produto) {
    int i,j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 12; j++)
            printf("%d ", produto->quant[i][j]);
}
