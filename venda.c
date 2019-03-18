#include "venda.h"

#define CAMPOSVENDA 7

/**
  \brief Estrutura para guardar uma venda.
  */
struct venda {
    char* codProd;    /**< código de produto */
    char* codCli;     /**< código de clientes */
    double precoUnit; /**< preço unitário */
    int quantidade;   /**< quantidade comprada */
    char tipo;       /**< tipo de compra (N/P) */
    int mes;          /**< mês da compra */
    int filial;       /**< filial */
};

static char** saleFields(const char* sale) {
    int i;
    char** fieldOfSales = malloc(sizeof(char*) * CAMPOSVENDA);
    char* buff = malloc(strlen(sale) + 1);
    char* freee = buff;
    strcpy(buff, sale);
    buff = strtok(buff, " ");
    for(i = 0; i < CAMPOSVENDA && buff; i++) {
        fieldOfSales[i] = malloc(strlen(buff) + 1);
        strcpy(fieldOfSales[i], buff);
        buff = strtok(NULL, " ");
    }
    free(freee);
    return fieldOfSales;
}

int verifySale(const char* sale) {
    int r = 0, i;
    char** fieldOfSales = saleFields(sale);
    if(atoi(fieldOfSales[6]) > 3 || atoi(fieldOfSales[6]) < 1);
    else if(atoi(fieldOfSales[5]) > 12 || atoi(fieldOfSales[5]) < 1);
    else if(fieldOfSales[3][0] != 'P' && fieldOfSales[3][0] != 'N');
    else if(atoi(fieldOfSales[2]) > 250 || atoi(fieldOfSales[2]) < 0);
    else if(atof(fieldOfSales[1]) > 999.99 && atof(fieldOfSales[1]) < 0);
    else if(!searchClient(fieldOfSales[4]));
    else if(!searchProduct(fieldOfSales[0]));
    else r = 1;
    for(i = 0; i < CAMPOSVENDA; i++)
        free(fieldOfSales[i]);
    free(fieldOfSales);
    return r;
}

Venda mkSale(const char* sale) {
    int i;
    char** fieldOfSales = malloc(sizeof(char*) * CAMPOSVENDA);
    Venda venda = malloc(sizeof(struct venda));
    fieldOfSales = saleFields(sale);
    venda->codProd = malloc(strlen(fieldOfSales[0]) + 1);
    strcpy(venda->codProd, fieldOfSales[0]);
    venda->precoUnit = atof(fieldOfSales[1]);
    venda->quantidade = atoi(fieldOfSales[2]);
    venda->tipo = fieldOfSales[3][0];
    venda->codCli = malloc(strlen(fieldOfSales[4]) + 1);
    strcpy(venda->codCli, fieldOfSales[4]);
    venda->mes = atoi(fieldOfSales[5]);
    venda->filial = atoi(fieldOfSales[6]);
    for(i = 0; i < CAMPOSVENDA; i++)
        free(fieldOfSales[i]);
    free(fieldOfSales);

    return venda;
}
