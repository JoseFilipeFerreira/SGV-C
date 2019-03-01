#include "clientes.h"
#include "produtos.h"
#include "vendas.h"

char* vendas[1000000];
int salesNumber;

void readSalesFile(char* path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(35);
    for(i = 0; fgets(buff, 35, f); i++) {
        vendas[i] = malloc(35);
        strcpy(vendas[i], buff);
    }
    salesNumber = i;
    fclose(f); 
}

void readVendas() {
    readSalesFile("db/Vendas_1M.txt");
}

void verifySales() {
    int r, w, i;
    char* buff = malloc(10);
    char* tempSale;
    char* fieldOfSales[7];
    FILE* f = fopen("db/Vendas_1MValidas.txt", "w");
    for(r = w = 0; r < salesNumber; r++) {
        tempSale = malloc(strlen(vendas[r]) + 1);
        strcpy(tempSale, vendas[r]);
        buff = strtok(tempSale, " ");
        for(i = 0; i < 7 && buff; i++) {
            fieldOfSales[i] = malloc(strlen(buff) + 1);
            strcpy(fieldOfSales[i], buff);
            buff = strtok(NULL, " ");
        }
        if(atoi(fieldOfSales[6]) > 3 || atoi(fieldOfSales[6]) < 1);
        else if(atoi(fieldOfSales[5]) > 12 || atoi(fieldOfSales[5]) < 1);
        else if(fieldOfSales[3][0] != 'P' && fieldOfSales[3][0] != 'N');
        else if(atoi(fieldOfSales[2]) > 250 || atoi(fieldOfSales[2]) < 0);
        else if(atof(fieldOfSales[1]) > 999.99 && atof(fieldOfSales[1]) < 0);
        else if(!searchClient(fieldOfSales[4]));
        else if(!searchProduct(fieldOfSales[0]));
        else {
            fprintf(f, "%s", vendas[r]);
            if(w != r) {
                vendas[w] = malloc(35);
                strcpy(vendas[w], vendas[r]);
                free(vendas[r]);
            }
            w++;
        }
    }
    fclose(f);
    salesNumber = w;
}

int getSalesNumber() {
    return salesNumber;
}

void initDB() {
    initProducts();
    initClients();
    readVendas();
    verifySales();
}
