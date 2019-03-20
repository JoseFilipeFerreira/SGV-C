#include "controler.h"

#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KORG  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KROXO "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KGREY "\x1B[37m"
#define KWHT  "\x1B[38m"
#define BOLD  "\033[1m"
#define UNDER "\033[4m"
#define BLINK "\033[5m"

#define RESET "\033[0m"

#define HIDE_CURSOR "\x1B[?25l"
#define SHOW_CURSOR "\x1B[?25h"

#define BACK 0
#define EXIT -1
#define MAX_FILE_NAME 256

static void menuClientes();
static void menuProdutos();
static void menuVendas();
static void menuCategories(int* loop, Tudo tudo);
static void menuLoadFile(int* loop, Tudo* tudo);
static void menuLoadCustom(int* loop, Tudo* tudo);

void menuPaginasDraw(char* header, char** tab, int size, int sizePage, int nCols){
    char search;
    int lPrinted, page = 0;
    /*calcular número de páginas*/
    int nPages = (size % (sizePage * nCols))?(size/(sizePage*nCols)) : size/(sizePage*nCols) - 1;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s--\n\n" RESET, header);

        lPrinted = printStrings(tab, size, sizePage, nCols, page);

        replicate("\n", sizePage - lPrinted  + 2);
        printf("\t\t%d/%d [n/p/b]\n", page + 1 , nPages+1);
        search = getchar();
        search = (search >= 'A' && search <= 'Z')?search - 'A':search;
        switch (search)
        {
            case 'n':
                /*não permite página maior que permitido*/
                page = (page + 1 <= nPages)?page + 1 : page;
                break;
            
            case 'p':
                /*não permite páginas negativas*/
                page = (page - 1 >= 0)?page -1 : page;
                break;
            
            case 'b':
                return;
        
            default:
                break;
        }
    }
}

void menuInicial(){ 
    int loop = 1;
    Tudo tudo;
    menuLoadFile(&loop, &tudo);

    printf(SHOW_CURSOR);
    system("clear");

    destroyTudo(tudo);
}

void menuLoadFile(int* loop, Tudo* tudo){
    int r;
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Load Files [1] --\n\n" RESET);
        printf("1 - Load Default (filtered)\n");
        printf("2 - Load Default (non filtered)\n");
        printf("3 - Load Custom\n");
        printf("e - EXIT\n");
        r = menuCheck(3);
        system("clear");
        printf(HIDE_CURSOR);
        printf(BLINK "LOADING...\n" RESET);
        fflush(stdout);
        switch (r)
            {
                case 1:
                   *tudo = tudoInicializadoFilter("db/Clientes.txt", "db/Produtos.txt", "db/Vendas_1M.txt");
                   menuCategories(loop, *tudo);
                   break;

                case 2:
                    *tudo = tudoInicializadoNoFilter("db/Clientes.txt", "db/Produtos.txt", "db/Vendas_1M.txt");
                    menuCategories(loop, *tudo);
                    break;
            
                case 3:
                   menuLoadCustom(loop, *tudo);
                   break;
                
                case EXIT:
                    *loop = 0;
                    break;

                default:
                    break;
            }
        }
}

void lCustomSingle(char* fstPrint,char* sndPrint, char* buf, int* filter){
    int aR, fl = 0;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Load Custom --\n" RESET);

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
        aR = access(buf, R_OK);
        if( aR != -1 ) {
           *filter = messageCheck(sndPrint);
           break;
        }
        else {
            fl = 1;   
        }
    }
}

void menuLoadCustom(int* loop, Tudo* tudo){
    char * bufCli = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufProd = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufSales = malloc(sizeof(char) * MAX_FILE_NAME);
    int filterCli, filterProd, filterSales;
    printf(SHOW_CURSOR);

    lCustomSingle("Nome ficheiro de Clientes:\n", "Filter clientes", bufCli, &filterCli);

    lCustomSingle("Nome ficheiro de Produtos:\n", "Filter produtos", bufProd, &filterProd);

    lCustomSingle("Nome ficheiro de Vendas:\n", "Filter vendas", bufSales, &filterSales);

    system("clear");
    printf(HIDE_CURSOR);
    printf(BLINK "LOADING...\n" RESET);
    fflush(stdout);

    *tudo = (filterCli || filterProd || filterSales) ? tudoInicializadoFilter(bufCli, bufProd, bufSales) : tudoInicializadoNoFilter(bufCli, bufProd, bufSales);

    free(bufCli);
    free(bufProd);
    free(bufSales);

    printf(SHOW_CURSOR);

    menuCategories(loop, *tudo);
}

void menuCategories(int* loop, Tudo tudo){
    while(*loop){
        system("clear");
        printf(SHOW_CURSOR);
        printf(BOLD KRED "\t-- Categoria --\n\n" RESET);
        printf("1 - Clientes\n");
        printf("2 - Produtos\n");
        printf("3 - Vendas\n");
        printf("e - EXIT\n");
        switch (menuCheck(3))
        {
            case 1:
               menuClientes(loop, tudo);
               break;

            case 2:
                menuProdutos(loop, tudo);
                break;

            case 3:
                menuVendas(loop, tudo);
                break;

            case EXIT:
                *loop = 0;
                break;

            default:
                break;
        }
    }
}

/**
@brief Query 7
*/
void tabClientAno(Tudo tudo){
    int i, j, r = 0;
    char* buf = malloc(sizeof(char) * 10);
    while(1){
        system("clear");
        printf(BOLD KRED "\t\t-- Clientes [7/12]--\n" RESET);

        if(r)
            printf(UNDER "Cliente não existe\n\n" RESET);
        else
            printf("\n\n");

        printf("Inserir Cliente a pesquisar:\n");

        fgets(buf, 10, stdin);
        buf = strtok(buf, "\n");

        if(searchClient(getClientesTodos(tudo), buf))
            break;
        else
            r = 1;
    }

    system("clear");
    printf(BOLD KRED "\t\t-- Clientes [7/12]--\n\n" RESET);
    printf("Cliente: %s\n\n", buf);

    int** iT = malloc(sizeof(int*) * 3);
    for (i=0; i<3; i++) {
        iT[i] = malloc(sizeof(int) * 12);
        for (j=0; j<12; j++)
            iT[i][j] = i;
    }



    printf("Produtos Comprados [7]:\n");

    printTabela(
        (const char *[]){ "Filial 1", "Filial 2", "Filial 3" },
        (const char *[]){ "JAN",
                          "FEV",
                          "MAR",
                          "ABR",
                          "MAI",
                          "JUN",
                          "JUL",
                          "AGO",
                          "SET",
                          "OUT",
                          "NOV",
                          "DEZ" },
        iT,
        3,
        12);
    getchar();
    free(buf);
}

void menuClientes(int* loop, Tudo tudo){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Clientes --\n\n" RESET);
        printf("1 - Clientes em todas as filiais [5]\n");
        printf("2 - Clientes que não compraram   [6]\n");
        printf("3 - Stats sobre cliente (ano)    [7/12]\n");
        printf("4 - Stats sobre cliente (mes)    [10]\n");
        switch (menuCheck(4))
        {
            case BACK:
                menuCategories(loop, tudo);
                break;

            case 1:
                break;

            case 2:
                break;

            case 3:
                tabClientAno(tudo);
                break;

            case 4:
                break;

            default:
                break;
        }
    }
}

/**
@brief Query 2
*/
void prodPages(Tudo tudo){
    char search;
    char** prodTab;
    int sizeProdTab;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Produtos [2]--\n\n" RESET);
        printf("Caracter a pesquisar:\n");
        search = getchar();
        if(search >= 'A' && search <= 'Z')
            break;
    }

    sizeProdTab = getProductLetter(getProdutosTodos(tudo), search, &prodTab);
    menuPaginasDraw("Produtos [2]", prodTab, sizeProdTab,15 , 6);

    free(prodTab);
}

void menuProdutos(int* loop, Tudo tudo){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Produtos --\n\n" RESET);
        printf("1 - Navegar Produtos por Letra     [2]\n");
        printf("2 - Informações de Produto por mês [3]\n");
        printf("3 - Produtos não comprados         [4]\n");
        printf("4 - Stats de produto numa filial   [9]\n");
        printf("5 - Produtos mais vendidos         [11]\n");
        switch (menuCheck(5))
        {
            case BACK:
                menuCategories(loop, tudo);
                break;

            case 1:
                prodPages(tudo);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;
            
            case 5:
                break;

            default:
                break;
        }
    }
}

void menuVendas(int* loop, Tudo tudo){
    while(*loop){
        system("clear");
        printf(BOLD KRED "\t-- Vendas --\n\n" RESET);
        printf("1 - total faturado em intervalo de tempo [8]\n");
        printf("2 - \n");
        printf("3 - \n");
        printf("4 - \n");
        switch (menuCheck(1))
        {
            case BACK:
                menuCategories(loop, tudo);
                break;

            case 1:
                break;

            default:
                break;
        }
    }
}
