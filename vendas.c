#include "vendas.h"

#define CAMPOSVENDA 7

/**
  \brief Array que contem as vendas.
  */
char* vendas[1000000];

/**
  \brief Número de vendas no array vendas.
  */
int salesNumber;

/**
  \brief Lê os produtos de um ficheiro e coloca-os no array vendas.

  @param path ficheiro onde estão as vendas
  */
static int readSalesFile(char* path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(35);
    for(i = 0; fgets(buff, 35, f); i++) {
        vendas[i] = malloc(35);
        strcpy(vendas[i], buff);
    }
    salesNumber = i;
    free(buff);
    fclose(f);
   return i; 
}

/**
  \brief Filtra as vendas do array de vendas.
  */
static void verifySales(const Produtos p, const Clientes c) {
    int r, w, i;
    FILE* f = fopen("db/VendasOK.txt", "w");
    for(r = w = 0; r < salesNumber; r++) {
        if(verifySale(vendas[r], p, c)){
            fprintf(f, "%s", vendas[r]);
            if(w != r) {
                free(vendas[w]);
                vendas[w] = malloc(strlen(vendas[r]) + 1);
                strcpy(vendas[w], vendas[r]);
                Venda venda = mkSale(vendas[w]);
                destroySale(venda);
            }
            w++;
        }
    }
    for(i = w; i < r; i++)
        free(vendas[i]);
    fclose(f);
    salesNumber = w;
}

int getSalesNumber() {
    return salesNumber;
}

void clearSales() {
    int i;
    for(i = 0; i < salesNumber; i++)
        free(vendas[i]);
}

int initDB(int filter, char* pathVendas, const Produtos p, const Clientes c){
    int r = readSalesFile(pathVendas);
    if (filter) verifySales(p, c);
    return r;
}

