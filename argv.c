#include "argv.h"

#include <time.h>

void argvParser(int argc, char** argv){
    clock_t start, end;
    double cpu_time_used;
    char** bloatTab;
    Tudo tudo;
    Inicializador i;

    start = clock();
    i = initInicial();
    setClientPath(i, "db/Clientes.txt", 1);
    setProductPath(i, "db/Produtos.txt", 1);
    setSalePath(i, "db/Vendas_1M.txt", 1);
    tudo = tudoInicializado(i);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time used to Load Files:%f\n", cpu_time_used );

    start = clock();
    switch(atoi(argv[1])){
        case 1: /* Answer all querys */
            /*1*/
            getTudoProductLetter( tudo, 'A', &bloatTab);
            /*4*/
            prodsNaoComprados(tudo, 3, &bloatTab);
            /*8*/
            getNSalesMes(tudo, 1, 12);
            getTFactMes(tudo, 1, 12);

            free(bloatTab);
            break;

        case 2:
            getTudoProductLetter(
                tudo,
                (argc == 3 && argv[2][0] >= 'A' && argv[2][0] <= 'Z') ? argv[2][0] : 'A',
                &bloatTab);
            free(bloatTab);
            break;

        case 3:
            break;
        case 4:
            prodsNaoComprados(
                tudo,
                (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 3,
                &bloatTab);
            free(bloatTab);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            getNSalesMes(tudo, 1, 12);
            getTFactMes(tudo, 1, 12);
            break;

        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        default:
            break;      
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time used to Answer Query:%f\n", cpu_time_used );
    start = clock();

    destroyInit(i);
    destroyTudo(tudo);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time used to Free structs:%f\n", cpu_time_used );
}