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
}

void readVendas() {
    readSalesFile("./db/Vendas_1M.txt");
}

void verifySales() {
    int r, w, quantity, filial, month;
    float price;
    char* product = malloc(10);
    char* client = malloc(10);
    char saleType;
    FILE* f = fopen("./db/Vendas_1MValidas.txt", "w");
    for(r = w = 0; r < salesNumber; r++) {
        sscanf(vendas[r], "%s %f %d %c %s %d %d%*2c", product, &price, &quantity, &saleType, client, &month, &filial);
        if(filial > 3 || filial < 1);
        else if(month > 12 || month < 1);
        else if(!searchClient(client));
        else if(saleType != 'P' && saleType != 'N');
        else if(quantity > 250 || quantity < 0);
        else if(price > 999.99 && price < 0);
        else if(!searchProduct(product));
        else {
            fprintf(f, "%s", vendas[r]);
            if(w != r)
                strcpy(vendas[w], vendas[r]);
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
