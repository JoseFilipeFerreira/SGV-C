#include "sgv.h"

#include <stdio.h>
/**
@brief Guardar a base de dados 
*/
struct sgv {
    Produtos produtos; /**< Todos os produtos lidos */
    Clientes clientes; /**< Todos os clientes lidos */
    Faturas faturas;   /**< Todas as faturas lidas */
    Filiais filiais[3];
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

SGV sgvInicializado(Inicializador i) {
    SGV sgv = malloc(sizeof(struct sgv));
    int is;
    FILE* f = fopen(i->pathP, "r");
    char* buff = malloc(35);
    Faturas faturas = initFaturas();
    Clientes clientes = initClients(); 
    for(is = 0; is < 3; is++) 
        sgv->filiais[is] = filialInit();
    Produtos produtos = initProducts(); 
    for(i->productLines = 0; fgets(buff, 10, f); i->productLines++) {
        Produto product = mkProduct(buff);
        char* id = getIdProduct(product);
        if(!i->filterProducts || verifyProduct(id)) {
            addProduct(product, produtos);
        }
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
    
    f = fopen(i->pathV, "r");
    for(i->salesLines = i->salesNumber = 0; fgets(buff, 35, f); i->salesLines++) {
        if(!i->filterSales || verifySale(buff, produtos, clientes)) {
                Venda venda = mkSale(buff);
                char* idP = getProductSale(venda); 
                char* id = getClientSale(venda);
                produtosUpdateCompra(idP, getFilialSale(venda), produtos);
                free(idP);
                addFatura(venda, faturas);
                i->salesNumber++;
                filialUpdate(sgv->filiais[getFilialSale(venda)], venda);
                clientesUpdateCompra(id, getFilialSale(venda), clientes); 
                destroySale(venda);
                free(id);
        }
    }
    fclose(f);
    free(buff);
    i->productNumber = getProductNumber(produtos);
    i->clientNumber = getClientNumber(clientes);
    sgv->produtos = produtos;
    sgv->clientes = clientes;
    sgv->faturas = faturas;
    return sgv;
}

Produtos getProdutosTodos(const SGV sgv) {
    return sgv->produtos;
}

Clientes getClientesTodos(const SGV sgv) {
    return sgv->clientes;
}

void setProduto(SGV sgv, const Produtos p) {
    sgv->produtos = p;
}

void setCliente(SGV sgv, const Clientes p) {
    sgv->clientes = p;
}

void destroySGV(SGV sgv) {
    int i;
    clearProducts(sgv->produtos);
    clearClients(sgv->clientes);
    clearFaturas(sgv->faturas);
    for(i = 0; i < 3; i++)
        destroyFilial(sgv->filiais[i]);
    free(sgv);
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

int getNSalesMes(const SGV sgv, int inicio, int fim) {
    int r;
    Faturas f = sgv->faturas;
    for(r = 0; inicio <= fim; inicio++)
        r += getQuantTotal(f, inicio);
    return r;
}

double getTFactMes(const SGV sgv, int inicio, int fim) {
    double r;
    Faturas f = sgv->faturas;
    for(r = 0; inicio <= fim + 1; inicio++)
        r += getFatTotal(f, inicio);
    return r;
}

int getProdNComprados(const SGV sgv) {
    return getProductNumber(sgv->produtos) - getProdsVendidos(sgv->faturas); 
}

int getClientesNCompradores(const SGV sgv) {
    return getClientesNaoCompradores(sgv->clientes);
}

int prodsNaoComprados(const SGV sgv, const Filial filial, char*** array) {
    return getNaoComprados(sgv->produtos, filial, array);
}

int clientesCompraramFilial (const SGV sgv, char*** array) {
    return getComprador(sgv->clientes, array);
}

void destroyInit(Inicializador inicial) {
    free(inicial->pathC);
    free(inicial->pathP);
    free(inicial->pathV);
    free(inicial);
}

int getSGVProductLetter(const SGV sgv, const char id, char*** array){
    return getProductLetter(getProdutosTodos(sgv),  id, array);
}

int searchSGVProduct(SGV sgv, char* produto){
    return searchProduct(getProdutosTodos(sgv), produto);
}

int searchSGVClient(SGV sgv, char* cliente){
    return searchClient(getClientesTodos(sgv), cliente);
}

double getFatMesSGV(const SGV sgv, const char* id, Tipo tipo, Filial filial, int mes) {
    FatP t = searchFatura(sgv->faturas, id);
    if(t) 
        return getFatMesFilial(t, tipo, filial, mes);
    return 0;
} 

FatP* getMaisVendidos(const SGV sgv, int* N) {
    return getAllList(sgv->faturas, N);
}

int getNVendasFat(const SGV sgv, const char* id, Tipo tipo, Filial filial, int mes) {
    return getNVendasFaturas(sgv->faturas, id, mes, filial, tipo);
}

int getClientQuantSGV(const char* id, int mes, int filial, const SGV sgv) {
    return getClientQuant(id, mes, sgv->filiais[filial]);
}

int sgvQuantosCompraramProdutos(const char* id, int filial, SGV sgv) {
    return produtosQuantosCompraram(id, sgv->filiais[filial]);
}

Compradores sgvQuemComprouProduto(const char* id, Filial filial, SGV sgv) {
    return produtoQuemComprou(sgv->filiais[filial], id);
}

int getQuantMesSGV(const SGV sgv, const char* id, Filial filial) {
    FatP t = searchFatura(sgv->faturas, id);
    if(t) 
        return getQuantMesFilial(t, filial);
   return 0;
}

int sgvGetMaisVendidosCliente(const SGV sgv, const char* id, char*** array) {
    return getMaisVendidosCliente(sgv->filiais, id, 3, array);
}

int sgvGetMaisCompradosCliente(const SGV sgv, const char* id, char*** array, int mes) {
    return getMaisCompradosCliente(sgv->filiais, id, array, mes);
}
