#include "init.h"

/**
@brief Guardar a base de dados 
*/
struct tudo {
    Produtos produtos; /**< Todos os produtos lidos */
    Clientes clientes; /**< Todos os clientes lidos */
};

/**
@brief Indica como inicializar a base de dados
*/
struct inicializador {

    char* pathC; /**< Caminho para o ficheiro de Clientes */
    int clientLines; /**< Número de linhas no ficheiro de Clientes */
    int clientNumber; /**< Número de linhas válidas no ficheiro de Clientes */
    int filterClients; /**< Indica se é para filtar o ficheiro de Clientes */

    char* pathP; /**< Caminho para o ficheiro de Produtos */
    int productLines; /**< Número de linhas no ficheiro de Produtos */
    int productNumber; /**< Número de linhas válidas no ficheiro de Produtos */
    int filterProducts; /**< Indica se é para filtar o ficheiro de Produtos */

    char* pathV; /**< Caminho para o ficheiro de Vendas */
    int salesLines; /**< Número de linhas no ficheiro de Vendas */
    int salesNumber; /**< Número de linhas válidas no ficheiro de Vendas */
    int filterSales; /**< Indica se é para filtar o ficheiro de Vendas */
};

Tudo tudoInicializado(Inicializador i) {
    Tudo tudo = malloc(sizeof(struct tudo));
    FILE* f = fopen(i->pathP, "r");
    char* buff = malloc(10);
    Clientes clientes = initClients(); 

    Produtos produtos = initProducts(); 
    for(i->productLines = 0; fgets(buff, 10, f); i->productLines++) {
        Produto product = mkProduct(buff);
        char* id = getIdProduct(product);
        if(!i->filterProducts || verifyProduct(id))
            addProduct(product, produtos);
        else
            destroyProduct(product);
        free(id);
    }
    fclose(f);

    f = fopen(i->pathC, "r");

    for(i->clientLines = 0; fgets(buff, 10, f); i->clientLines++) {
        Cliente client = mkClient(buff);
        char* id = getIdClient(client);
        if(!i->filterClients || verifyClient(id))
            addClient(client, clientes);
        else
            destroyClient(client);
        free(id);
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

char* getSalePath(const Inicializador i) {
    char* r = malloc(strlen(i->pathV) + 1);
    strcpy(r, i->pathV);
    return r;
}

char* getProductPath(const Inicializador i) {
    char* r = malloc(strlen(i->pathP) + 1);
    strcpy(r, i->pathP);
    return r;
}

char* getClientPath(const Inicializador i) {
    char* r = malloc(strlen(i->pathC) + 1);
    strcpy(r, i->pathC);
    return r;
}

void destroyInit(Inicializador inicial) {
    free(inicial->pathC);
    free(inicial->pathP);
    free(inicial->pathV);
    free(inicial);
}
