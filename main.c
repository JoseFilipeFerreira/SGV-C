/**
@file main.c
\brief Ficheiro principal.
*/
#include "init.h"
#include "controler.h"

/**
\brief Função principal.
*/
int main(int argc, char** argv) {
    if (argc > 1) {
        menuInicial();
    }
    else {
        Tudo tudo = tudoInicializado("db/Clientes.txt", "db/Produtos.txt", "db/Vendas_1M.txt", 1);
        Produtos produtos = getProdutosTodos(tudo);
        Clientes clientes = getClientesTodos(tudo);
        printf("N de produtos: %d\n", getProductNumber(produtos));
        printf("N de Clientes: %d\n", getClientNumber(clientes));
        printf("N de Vendas: %d\n", getSalesNumber());
        destroyTudo(tudo);    
    }
    return 0;
}
