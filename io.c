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
        printf("%s\n", s[i]);
        r++;
    }
    return r;
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

void menuLoadCustom(int* loop){
    char * bufCli = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufProd = malloc(sizeof(char) * MAX_FILE_NAME);
    char * bufSales = malloc(sizeof(char) * MAX_FILE_NAME);
    int filterCli, filterProd, filterSales;
    printf(SHOW_CURSOR);
    while(1){
         system("clear");
         printf(BOLD KRED "\t-- Load Custom --\n\n" RESET);
         printf("Nome ficheiro de Clientes:\n");
         fflush(stdout);
         fgets(bufCli, MAX_FILE_NAME, stdin);
         bufCli = strtok(bufCli, "\n");
         if( access(bufCli, R_OK ) != -1 ) {
            filterCli = messageCheck("Filter clientes");
            break;
         }
    }

    while(1){
         system("clear");
         printf(BOLD KRED "\t-- Load Custom --\n\n" RESET);
         printf("Nome ficheiro de Produtos:\n");
         fflush(stdout);
         fgets(bufProd, MAX_FILE_NAME, stdin);
         bufProd = strtok(bufProd, "\n");
         if( access(bufProd, R_OK ) != -1 ) {
            filterProd = messageCheck("Filter produtos");
            break;
         }
    }

    while(1){
         system("clear");
         printf(BOLD KRED "\t-- Load Custom --\n\n" RESET);
         printf("Nome ficheiro de Vendas:\n");
         fflush(stdout);
         fgets(bufSales, MAX_FILE_NAME, stdin);
         bufSales = strtok(bufSales, "\n");
         if( access(bufSales, R_OK ) != -1 ) {
            filterSales = messageCheck("Filter vendas");
            break;
         }
    }

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
                break;

            case 4:
                break;

            default:
                break;
        }
    }
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
