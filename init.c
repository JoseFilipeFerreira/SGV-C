#include "init.h"

struct tudo {
    Produtos produtos;
    Clientes clientes;
};

static Tudo tudoInicializado(const char* pathC, const char* pathP, const char* pathV, int filter) {
    Tudo tudo = malloc(sizeof(struct tudo));
    FILE* f = fopen(pathP, "r");
    char* buff = malloc(10);

    Produtos produtos = initProducts(); 
    while(fgets(buff, 10, f)) {
        Produto product = mkProduct(buff);
        if(!filter || verifyProduct(getIdProduct(product)))
            addProduct(product, produtos);
        else
            destroyProduct(product);
    }
    fclose(f);

    f = fopen(pathC, "r");
    Clientes clientes = initClients(); 
    while(fgets(buff, 10, f)) { 
        Cliente client = mkClient(buff);
        if(!filter || verifyClient(getIdClient(client)))
            addClient(client, clientes);
        else
            destroyClient(client);
    }
    fclose(f);
    free(buff);
    initDB(filter, pathV, produtos, clientes);
    tudo->produtos = produtos;
    tudo->clientes = clientes;
    return tudo;
}

Tudo tudoInicializadoFilter(const char* pathC, const char* pathP, const char* pathV) {
    return tudoInicializado(pathC, pathP, pathV, 1);
}

Tudo tudoInicializadoNoFilter(const char* pathC, const char* pathP, const char* pathV) {
    return tudoInicializado(pathC, pathP, pathV, 0);
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
