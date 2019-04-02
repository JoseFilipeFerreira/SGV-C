#include "argv.h"

#include <time.h>
#include <stdio.h>

void argvParser(int argc, char** argv){
    clock_t start, end;
    double cpu_time_used;
    char** bloatTab;
    char* prod, *cli;
    int v1, v2, mes;
    SGV sgv;
    Inicializador i;

    start = clock();
    i = initInicial();
    setClientPath(i, "db/Clientes.txt", 1);
    setProductPath(i, "db/Produtos.txt", 1);
    setSalePath(i, "db/Vendas_1M.txt", 1);
    sgv = sgvInicializado(i);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Load Files:%f\n", cpu_time_used );

    start = clock();
    switch(atoi(argv[1])){
        case 1: /* Answer all querys */
            /*2*/
            getSGVProductLetter( sgv, 'A', &bloatTab);
            /*3*/
            for(v1 = 0; v1 < 3; v1++){
                getFatMesSGV  (sgv, "ZZ1999", N, v1, 1);
                getFatMesSGV  (sgv, "ZZ1999", P, v1, 1);
                getQuantMesSGV(sgv, "ZZ1999", N, v1, 1);
                getQuantMesSGV(sgv, "ZZ1999", P, v1, 1);
            }
            /*4*/
            prodsNaoComprados(sgv, 3, &bloatTab);
            /*5*/
            clientesCompraramFilial(sgv, &bloatTab);
            /*6*/
            getClientesNCompradores(sgv);
            getProdNComprados(sgv);
            /*7*/
            for (v1=0; v1<3; v1++)
                for (v2=0; v2<12; v2++)
                    getClientQuantSGV("A1234", v1, v2, sgv);
            /*8*/
            getNSalesMes(sgv, 1, 12);
            getTFactMes(sgv, 1, 12);

            free(bloatTab);
            break;

        case 2:
            getSGVProductLetter(
                sgv,
                (argc == 3 && argv[2][0] >= 'A' && argv[2][0] <= 'Z') ? argv[2][0] : 'A',
                &bloatTab);
            free(bloatTab);
            break;

        case 3:
            prod = (argc == 3 && searchSGVProduct(sgv, argv[2]))?argv[2] :  "ZZ1999";
            mes  =    (argc == 4 && atoi(argv[3]))? atoi(argv[3]) : 1;
            for(v1 = 0; v1 < 3; v1++){
                getFatMesSGV  (sgv, prod, N, v1, mes);
                getFatMesSGV  (sgv, prod, P, v1, mes);
                getQuantMesSGV(sgv, prod, N, v1, mes);
                getQuantMesSGV(sgv, prod, P, v1, mes);
            }
            break;
        case 4:
            prodsNaoComprados(
                sgv,
                (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 3,
                &bloatTab);
            free(bloatTab);
            break;
        case 5:
            clientesCompraramFilial(sgv, &bloatTab);
            free(bloatTab);
            break;
        case 6:
            getClientesNCompradores(tudo);
            getProdNComprados(tudo);
            break;
        case 7:
            cli = (argc == 3 && searchSGVClient(sgv, argv[2]))?argv[2] :  "A1234";
            for (v1=0; v1<3; v1++)
                    for (v2=0; v2<12; v2++)
                        getClientQuantSGV(cli, v1, v2, sgv);
            break;
        case 8:
            v1 = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 1;
            v2 = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 12;
            getNSalesMes(sgv, v1, v2);
            getTFactMes(sgv, v1, v2);
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
    destroySGV(sgv);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Free structs:%f\n", cpu_time_used );
}