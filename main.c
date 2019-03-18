/**
@file main.c
\brief Ficheiro principal.
*/
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"
#include "io.h"

/**
\brief Função principal.
*/
int main(int argc, char ** argv) {
    if (argc > 1){
        menuInicial();
    }
    else{
        initDB(1, "db/Produtos.txt", "db/Clientes.txt", "db/Vendas_1M.txt");
        printf("N de vendas: %d\n", getProductNumber());
        printf("N de clientes: %d\n", getClientNumber());
        printf("N de vendas: %d\n", getSalesNumber());
        
        clearClients();
        clearProducts();
        clearSales();
    }
    
    return 0;
}
