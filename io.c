#include "io.h"

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
static void menuCategories(int* loop);
static void menuLoadFile(int* loop);
static void menuLoadCustom(int* loop);

/**
@brief replicate a given string n times

@param s string to duplicate
@param n times to duplicate
 */
void replicate(char* s, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%s", s);
}

int menuCheck(int size){
    int r;
    char s[10];
    fgets(s,10,stdin);
    if(strlen(s) == 2){
        if (s[0] >= '0' && s[0] <= '9'){
            r = (int)s[0] - (int)'0';
            if(r > 0 && r <= size){
                return r;
            }
        }
        else{
            if(s[0] == 'b' || s[0] == 'B'){
                return BACK;
            }
            if(s[0] == 'e' || s[0] == 'E'){
                return EXIT;
            }
        }
    }
    return -2;
}





int printStrings(char** s, int ss, int pSize, int pN){
    int i, r = 0;

    for(i = pSize * pN; i < pSize * (pN + 1) && i < ss; i++){
        printf("%d.\t%s\n", i + 1, s[i]);
        r++;
    }
    return r;
}

void menuPaginasDraw(char* header, char** tab, int size, int sizePage){
    char search;
    int printed, page = 0;
    /*calcular número de páginas*/
    int nPages = (size % sizePage)?(size/sizePage) : size/sizePage - 1;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s--\n\n" RESET, header);
        printed = printStrings(tab, size, sizePage, page);
        replicate("\n", sizePage - printed + 1);
        printf("\t\t%d/%d [n/p/b]\n", page +1 , nPages+1);
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

int messageCheck(char* message){
    char s[10];
    printf("%s [Y/n]", message);
    fflush(stdout);
    while(1){
        fgets(s,10,stdin);
        if(s[0] == 'y' || s[0] == 'Y' || s[0] == '\n')
            return 1;
        if(s[0] == 'n' || s[0] == 'N')
            return 0;
    }
}

void menuInicial(){ 
    int loop = 1;
    menuLoadFile(&loop);

    printf(SHOW_CURSOR);
    system("clear");

    clearClients();
    clearProducts();
    clearSales();
}

void menuLoadFile(int* loop){
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
                   initDB(1, "db/Produtos.txt", "db/Clientes.txt", "db/Vendas_1M.txt");
                   menuCategories(loop);
                   break;

                case 2:
                    initDB(0, "db/Produtos.txt", "db/Clientes.txt", "db/Vendas_1M.txt");
                    menuCategories(loop);
                    break;
            
                case 3:
                   menuLoadCustom(loop);
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

void menuLoadCustom(int* loop){
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

    initDB(filterCli || filterProd || filterSales, bufProd, bufCli, bufSales);

    free(bufCli);
    free(bufProd);
    free(bufSales);

    printf(SHOW_CURSOR);

    menuCategories(loop);
}

void menuCategories(int* loop){
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
               menuClientes(loop);
               break;

            case 2:
                menuProdutos(loop);
                break;

            case 3:
                menuVendas(loop);
                break;

            case EXIT:
                *loop = 0;
                break;

            default:
                break;
        }
    }
}

void printTabela(const char* linLabl[], const char* colLabl[], int** iT, int lin, int col){
    int i, j;
    printf("+");
    replicate("-", strlen(linLabl[0]) + 2);
    for(j=0; j < col; j++)
        printf("+-----");
    printf("+\n");
    printf("|");
    replicate(" ", strlen(linLabl[0]) + 2);
    for(j = 0; j < col; j++)
        printf("| %s ", colLabl[j]);
    printf("|\n+");
    replicate("-", strlen(linLabl[1]) + 2);
    for(j=0; j < col; j++)
        printf("+-----");
    printf("+\n");
    
    for(i = 0; i < lin; i++){
        printf("| %s ", linLabl[i]);
        for(j = 0; j < col; j++)
            printf("|%4d ", iT[i][j]);
    printf("|\n+");
    replicate("-", strlen(linLabl[i]) + 2);
    for(j=0; j < col; j++)
        printf("+-----");
    printf("+\n");
    }
}

/**
@brief Query 7
*/
void tabClientAno(){
    int i, j;
    system("clear");
    printf(BOLD KRED "\t\t-- Clientes [7/12]--\n\n" RESET);

    int** iT = malloc(sizeof(int*) * 3);
    for (i=0; i<3; i++) {
        iT[i] = malloc(sizeof(int) * 12);
        for (j=0; j<12; j++)
            iT[i][j] = i;
    }

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
}

void menuClientes(int* loop){
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
                menuCategories(loop);
                break;

            case 1:
                break;

            case 2:
                break;

            case 3:
                tabClientAno();
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
void prodPages(){
    char search;
    char** prodTab;
    int sizeProdTab;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Produtos [2]--\n\n" RESET);
        printf("Caracter a pesquisar\n");
        search = getchar();
        if(search >= 'A' && search <= 'Z')
            break;
    }

    sizeProdTab = getProductLetter(search, &prodTab);
    menuPaginasDraw("Produtos [2]", prodTab, sizeProdTab, 15);
    free(prodTab);

}

void menuProdutos(int* loop){
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
                menuCategories(loop);
                break;

            case 1:
                prodPages();
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

void menuVendas(int* loop){
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
                menuCategories(loop);
                break;

            case 1:
                break;

            default:
                break;
        }
    }
}
