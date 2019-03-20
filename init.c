#include "init.h"

struct tudo {
    Produtos produtos;
    Clientes clientes;
};

struct inicializador {

    char* pathC;
    int clientLines;
    int clientNumber;
    int filterClients;

    char* pathP;
    int productLines;
    int productNumber;
    int filterProducts;

    char* pathV;
    int salesLines;
    int salesNumber;
    int filterSales;
};

Tudo tudoInicializado(Inicializador i) {
    Tudo tudo = malloc(sizeof(struct tudo));
    FILE* f = fopen(i->pathP, "r");
    char* buff = malloc(10);

    Produtos produtos = initProducts(); 
    for(i->productLines = 0; fgets(buff, 10, f); i->productLines++) {
        Produto product = mkProduct(buff);
        if(!i->filterProducts || verifyProduct(getIdProduct(product)))
            addProduct(product, produtos);
        else
            destroyProduct(product);
    }
    fclose(f);

    f = fopen(i->pathC, "r");
    Clientes clientes = initClients(); 
    for(i->clientLines = 0; fgets(buff, 10, f); i->clientLines++) {
        Cliente client = mkClient(buff);
        if(!i->filterClients || verifyClient(getIdClient(client)))
            addClient(client, clientes);
        else
            destroyClient(client);
    }
    fclose(f);
    free(buff);
    i->salesLines = initDB(i->filterSales, i->pathV, produtos, clientes);
    i->salesNumber = getSalesNumber();
    i->productNumber = getProductNumber(produtos);
    i->clientNumber = getClientNumber(clientes);
    tudo->produtos = produtos;
    tudo->clientes = clientes;
    return tudo;
}

Produtos getProdutosTodos(const Tudo tudo) {
    return tudo->produtos;
}

Clientes getClientesTodos(const Tudo tudo) {
    return tudo->clientes;
}

void setProduto(Tudo tudo, const Produtos p) {
    tudo->produtos = p;
}

void setCliente(Tudo tudo, const Clientes p) {
    tudo->clientes = p;
}

void destroyTudo(Tudo tudo) {
    clearProducts(tudo->produtos);
    clearClients(tudo->clientes);
    clearSales();
    free(tudo);
}

int getLinesClients(const Inicializador i) {
    return i->clientLines;
}

int getLinesProducts(const Inicializador i) {
    return i->productLines;
}

int getLinesSales(const Inicializador i) {
    return i->salesLines;
}

int getNumberClients(const Inicializador i) {
    return i->clientNumber;
}

int getNumberProducts(const Inicializador i) {
    return i->productNumber;
}

int getNumberSales(const Inicializador i) {
    return i->salesNumber;
}

void setClientPath(Inicializador i, const char* p, int f) {
    i->pathC = malloc(strlen(p) + 1);
    strcpy(i->pathC, p);
    i->filterClients = f;
}

void setProductPath(Inicializador i, const char* p, int f) {
    i->pathP = malloc(strlen(p) + 1);
    strcpy(i->pathP, p);
    i->filterProducts = f;
}

void setSalePath(Inicializador i, const char* p, int f) {
    i->pathV = malloc(strlen(p) + 1);
    strcpy(i->pathV, p);
    i->filterSales = f;
}

Inicializador initInicial() {
    Inicializador init = malloc(sizeof(struct inicializador));
    return init;
}

void destroyInit(Inicializador inicial) {
    free(inicial->pathC);
    free(inicial->pathP);
    free(inicial->pathV);
    free(inicial);
}
