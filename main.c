/**
@file main.c
\brief Ficheiro principal.
*/
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

/**
\brief Função principal.
*/
int main(int argc, char ** argv) {
    initDB(1);
    printf("%d %d %d\n", getSalesNumber(), getClientNumber(), getProductNumber());
    return 0;
}
