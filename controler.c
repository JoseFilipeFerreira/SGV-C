#include "controler.h"
#include "formating.h"

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void menuClientes   (int* loop, SGV* sgv);
static void menuProdutos   (int* loop, SGV* sgv);
static void menuVendas     (int* loop, SGV* sgv);
static void menuCategories (int* loop, SGV* sgv);
static void menuLoadFile   (int* loop, SGV* sgv);
static void menuLoadCustom (int* loop, SGV* sgv);

void startControler(){ 
    int loop = 1;
    SGV sgv = NULL;
    
    menuLoadFile(&loop, &sgv);

    printf(SHOW_CURSOR);
    system("clear");

    if(sgv) destroySGV(sgv);

}

void menuShowLoad(Inicializador i, double time){
    system("clear");
    printf(BOLD KRED "\t-- Load Info [1] --\n\n" RESET);

    printf(KGREY "Load Time: %f s%s\n\n", time, RESET);

    printf("Clientes Path:    %s\n", getClientPath(i));
    printf("Clientes Lidos:   %d\n", getLinesClients(i));
    printf("Clientes Válidos: %d\n\n", getNumberClients(i));

    printf("Produtos Path:    %s\n", getProductPath(i));
    printf("Produtos Lidos:   %d\n", getLinesProducts(i));
    printf("Produtos Válidos: %d\n\n", getNumberProducts(i));

    printf("Vendas Path:      %s\n", getSalePath(i));
    printf("Vendas Lidas:     %d\n", getLinesSales(i));
    printf("Vendas Válidas:   %d\n", getNumberSales(i));


    printf(HIDE_CURSOR);
    getchar();
    printf(SHOW_CURSOR);
}

void menuLoadFile(int* loop, SGV* sgv){
    int r;
    clock_t start, end;
    if(*sgv) destroySGV(*sgv);
    *sgv = NULL;
    while(*loop){
        Inicializador i;
        system("clear");
        printf(BOLD KRED "\t-- Load Files [1] --\n\n" RESET);
        printf("1 - Load Default\n");
        printf("2 - Load Custom\n");
        printf("e - EXIT\n");
        r = menuCheck(3);
        system("clear");
        printf(HIDE_CURSOR);
        printf(BLINK "LOADING...\n" RESET);
        fflush(stdout);
        switch (r)
        {
            case 1:
                i = initInicial();
                setClientPath(i, "db/Clientes.txt", 1);
                setProductPath(i, "db/Produtos.txt", 1);
                setSalePath(i, "db/Vendas_1M.txt", 1);
                start = clock();
                *sgv = sgvInicializado(i);
                end = clock();

                menuShowLoad(i, ((double) (end - start)) / CLOCKS_PER_SEC);
                menuCategories(loop, sgv);
                break;

            case 2:
                menuLoadCustom(loop, sgv);
                break;

            case EXIT:
                *loop = 0;
                break;

            default:
                break;
        }
    }
}

void lCustomSingle(char* fstPrint, char* buf, int* filter){
    int fl = 0;
    struct stat sb;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Load Custom [1]--\n" RESET);

        switch (fl)
        {
            case 1:
                printf(UNDER "Ficheiro Inválido\n\n" RESET);
                break;

            case 2:
                printf(UNDER "Ficheiro é uma pasta\n\n" RESET);
                break;

            default:
                printf("\n\n");
                break;
        }

        printf(fstPrint);
        fflush(stdout);
        fgets(buf, MAX_FILE_NAME, stdin);
        buf = strtok(buf, "\n");

        if (stat(buf, &sb) == 0 && S_ISDIR(sb.st_mode))
            fl = 2;
        else{
            if(access(buf, R_OK) != -1){
                *filter = 1;
                break;
            }
            else
                fl = 1;
        }
    }
}

void menuLoadCustom(int* loop, SGV* sgv){
    clock_t start, end;
    char * bufCli = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufProd = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufSales = malloc(sizeof(char) * MAX_FILE_NAME);
    int filterCli, filterProd, filterSales;
    Inicializador i; 
    printf(SHOW_CURSOR);

    lCustomSingle("Nome ficheiro de Clientes:\n", bufCli, &filterCli);
    lCustomSingle("Nome ficheiro de Produtos:\n", bufProd, &filterProd);
    lCustomSingle("Nome ficheiro de Vendas:\n", bufSales, &filterSales);

    system("clear");
    printf(HIDE_CURSOR);
    printf(BLINK "LOADING...\n" RESET);
    fflush(stdout);

    i = initInicial();
    setClientPath(i, bufCli, filterCli);
    setProductPath(i, bufProd, filterProd);
    setSalePath(i, bufSales, filterSales);
    start = clock();
    *sgv = sgvInicializado(i);
    end = clock();

    printf(SHOW_CURSOR);

    menuShowLoad(i, ((double) (end - start)) / CLOCKS_PER_SEC);
    menuCategories(loop, sgv);

    free(bufCli);
    free(bufProd);
    free(bufSales);
}

void menuCategories(int* loop, SGV* sgv){
    while(*loop){
        system("clear");
        printf(SHOW_CURSOR);
        printf(BOLD KRED "\t-- Categoria --\n\n" RESET);
        printf("1 - Clientes\n");
        printf("2 - Produtos\n");
        printf("3 - Vendas\n");
        printf("b - BACK\n");
        printf("e - EXIT\n");
        switch (menuCheck(3))
        {
            case 1:
                menuClientes(loop, sgv);
                break;

            case 2:
                menuProdutos(loop, sgv);
                break;

            case 3:
                menuVendas(loop, sgv);
                break;
            
            case BACK:
                menuLoadFile(loop, sgv);
                break;

            case EXIT:
                *loop = 0;
                break;

            default:
                break;
        }
    }
}

void menuClientes(int* loop, SGV* sgv){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Clientes --\n\n" RESET);
        printf("1 - Clientes em todas as filiais [5]\n");
        printf("2 - Clientes que não compraram   [6]\n");
        printf("3 - Stats sobre cliente (ano)    [7/12]\n");
        printf("4 - Stats sobre cliente (mes)    [10]\n");
        printf("b - BACK\n");
        switch (menuCheck(4))
        {
            case BACK:
                menuCategories(loop, sgv);
                break;

            case 1:
                clientesFieis(*sgv);
                break;

            case 2:
                clientesInfieis(*sgv);
                break;

            case 3:
                statsClientAno(*sgv);
                break;

            case 4:
                prodMaisCompradoCli(*sgv);
                break;

            default:
                break;
        }
    }
}

void menuProdutos(int* loop, SGV* sgv){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Produtos --\n\n" RESET);
        printf("1 - Navegar Produtos por Letra     [2]\n");
        printf("2 - Informações de Produto por mês [3]\n");
        printf("3 - Produtos não comprados         [4]\n");
        printf("4 - Stats de produto numa filial   [9]\n");
        printf("5 - Produtos mais vendidos         [11]\n");
        printf("b - BACK\n");
        switch (menuCheck(5))
        {
            case BACK:
                menuCategories(loop, sgv);
                break;

            case 1:
                prodPages(*sgv);
                break;

            case 2:
                prodStatsMes(*sgv);
                break;

            case 3:
                prodsNCompradosUI(*sgv);
                break;

            case 4:
                clientesCompraramProduto(*sgv);
                break;

            case 5:
                nMaisComprados(*sgv);
                break;

            default:
                break;
        }
    }
}

void menuVendas(int* loop, SGV* sgv){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Vendas --\n\n" RESET);
        printf("1 - total faturado em intervalo de tempo [8]\n\n\n\n");
        printf("b - BACK\n");
        switch (menuCheck(1))
        {
            case BACK:
                menuCategories(loop, sgv);
                break;

            case 1:
                tabVendasIntervalo(*sgv);
                break;

            default:
                break;
        }
    }
}
