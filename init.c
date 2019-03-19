#include "init.h"

struct tudo {
    Produtos produtos;
    Clientes clientes;
};

Tudo tudoInicializado(const char* pathC, const char* pathP, const char* pathV, int filter) {
    Tudo tudo = malloc(sizeof(struct tudo));
    FILE* f = fopen(pathP, "r");
    char* buff = malloc(10);
    
    Produtos produtos = initProducts(); 
    while(fgets(buff, 10, f)) {
        Produto product = mkProduct(buff);
        addProduct(product, produtos);
    }
    fclose(f);
    
    f = fopen(pathC, "r");
    Clientes clientes = initClients(); 
    while(fgets(buff, 10, f)) { 
        Cliente client = mkClient(buff);
        addClient(client, clientes);
    }
    fclose(f);
    free(buff);
    initDB(filter, pathV, produtos, clientes);
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

void destroyTudo(Tudo tudo) {
    clearProducts(tudo->produtos);
    clearClients(tudo->clientes);
    clearSales();
    free(tudo);
}
