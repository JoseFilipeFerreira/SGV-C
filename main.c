/**
@file main.c
\brief Ficheiro principal.
*/
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

/*
int messageCheck(char * message){
    int r = 1;
    char s[10];
    printf("%s[Y/n]\n", message);
    fgets(s,10,stdin);
    if(s[0] == 'n' || s[0] == 'N'){
        r = 0;
    }
    return r;
}
*/

/**
\brief Função principal.
*/
int main(int argc, char ** argv) {
    int r = 1;
    /*r = messageCheck("Would you like to filter the input?");*/
    initDB(r, "db/Produtos.txt", "db/Clientes.txt", "db/Vendas_1M.txt");
    printf("%d %d %d\n", getSalesNumber(), getClientNumber(), getProductNumber());

    clearClients();
    clearProducts();
    return 0;
}
