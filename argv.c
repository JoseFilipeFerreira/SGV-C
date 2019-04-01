#include "argv.h"

#include <time.h>
#include <stdio.h>

void argvParser(int argc, char** argv){
    clock_t start, end;
    double cpu_time_used;
    char** bloatTab;
    char* prod, *cli;
    int v1, v2, mes;
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
    fprintf(stderr, "CPU Time used to Load Files:%f\n", cpu_time_used );

    start = clock();
    switch(atoi(argv[1])){
        case 1: /* Answer all querys */
            /*2*/
            getTudoProductLetter( tudo, 'A', &bloatTab);
            /*3*/
            for(v1 = 0; v1 < 3; v1++){
                getFatMesTudo  (tudo, "ZZ1999", N, v1, 1);
                getFatMesTudo  (tudo, "ZZ1999", P, v1, 1);
                getQuantMesTudo(tudo, "ZZ1999", N, v1, 1);
                getQuantMesTudo(tudo, "ZZ1999", P, v1, 1);
            }
            /*4*/
            prodsNaoComprados(tudo, 3, &bloatTab);
            /*5*/
            clientesCompraramFilial(tudo, &bloatTab);
            /*6*/
            getClientesNCompradores(tudo);
            getProdNComprados(tudo);
            /*7*/
            for (v1=0; v1<3; v1++)
                for (v2=0; v2<12; v2++)
                    getClientQuantTudo("A1234", v1, v2, tudo);
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
            prod = (argc == 3 && searchTudoProduct(tudo, argv[2]))?argv[2] :  "ZZ1999";
            mes  =    (argc == 4 && atoi(argv[3]))? atoi(argv[3]) : 1;
            for(v1 = 0; v1 < 3; v1++){
                getFatMesTudo  (tudo, prod, N, v1, mes);
                getFatMesTudo  (tudo, prod, P, v1, mes);
                getQuantMesTudo(tudo, prod, N, v1, mes);
                getQuantMesTudo(tudo, prod, P, v1, mes);
            }
            break;
        case 4:
            prodsNaoComprados(
                tudo,
                (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 3,
                &bloatTab);
            free(bloatTab);
            break;
        case 5:
            clientesCompraramFilial(tudo, &bloatTab);
            free(bloatTab);
            break;
        case 6:
            getClientesNCompradores(tudo);
            getProdNComprados(tudo);
            break;
        case 7:
            cli = (argc == 3 && searchTudoClient(tudo, argv[2]))?argv[2] :  "A1234";
            for (v1=0; v1<3; v1++)
                    for (v2=0; v2<12; v2++)
                        getClientQuantTudo(cli, v1, v2, tudo);
            break;
        case 8:
            v1 = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 1;
            v2 = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 12;
            getNSalesMes(tudo, v1, v2);
            getTFactMes(tudo, v1, v2);
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
    fprintf(stderr, "CPU Time used to Answer Query:%f\n", cpu_time_used );
    start = clock();

    destroyInit(i);
    destroyTudo(tudo);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Free structs:%f\n", cpu_time_used );
}