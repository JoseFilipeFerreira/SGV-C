#include "produto.h"

struct product {
    char* id;
    int quantF[3];
    double totalF[3];
};

int verifyProduct(char* id) {
    char c1, c2;
    int n;
    sscanf(id, "%c%c%d%*s", &c1, &c2, &n);
    return strlen(id) == 6 && c1 <= 'Z' && c1 >='A' && c2 <= 'Z' && c2 >='A' && n >= 1000 && n <= 9999;
}

Product* mkProduct(char* id) {
    Product* product = NULL;
    if(verifyProduct(id)) {
        product = malloc(sizeof(struct product));
        product->id = malloc(strlen(id) + 1);
        strcpy(product->id, id);
        memset(product->quantF, 0, sizeof(product->quantF));
        memset(product->totalF, 0, sizeof(product->totalF));
    }
    return product;
}

void updateProduct(Product* product, int quantity, double price, int filial) {
    product->quantF[filial-1] += quantity;
    product->totalF[filial-1] += price;
}
