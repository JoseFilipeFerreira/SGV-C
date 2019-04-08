#include "argv.h"

#include <time.h>
#include <stdio.h>

/* Default query parameters */
#define DEFAULT_FIL  1
#define DEFAULT_MES_LOW 1
#define DEFAULT_MES_HIGH 12
#define DEAFULT_SIZE 20
#define DEFAULT_CHAR 'A'
#define DEFAULT_PROD "ZZ1999"
#define DEFAULT_CLI  "A1234"

void argvParser(int argc, char** argv){
    clock_t start, end;
    double cpu_time_used;

    char* prod, *cli;
    char** bloatTab;
    int i, j;
    int mes, nComprados;
    SGV sgv;
    FatP* fatArr;
    Inicializador init;
    Compradores compra;

    /*Benchmark Loading*/
    start = clock();
    init = initInicial();
    setClientPath (init, "db/Clientes.txt" , 1);
    setProductPath(init, "db/Produtos.txt" , 1);
    setSalePath   (init, "db/Vendas_1M.txt", 1);
    sgv = sgvInicializado(init);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Load Files:%f\n", cpu_time_used );

    start = clock();
    switch(atoi(argv[1])){
        case 1: /* Answer all querys */
            /*2*/
            i = getSGVProductLetter( sgv, DEFAULT_CHAR, &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            /*3*/
            for(i = 0; i < 3; i++){
                getFatMesSGV  (sgv, DEFAULT_PROD, N, i, 1);
                getFatMesSGV  (sgv, DEFAULT_PROD, P, i, 1);
                getNVendasFat(sgv, DEFAULT_PROD, N, i, 1);
                getNVendasFat(sgv, DEFAULT_PROD, P, i, 1);
            }
            /*4*/
            i = prodsNaoComprados(sgv, 3, &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            /*5*/
            i = clientesCompraramFilial(sgv, &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            /*6*/
            getClientesNCompradores(sgv);
            getProdNComprados(sgv);
            /*7*/
            for (i=0; i<3; i++)
                for (j=0; j<12; j++)
                    getClientQuantSGV(DEFAULT_CLI, j, i, sgv);
            /*8*/
            getNSalesMes(sgv, 1, 12);
            getTFactMes(sgv, 1, 12);
            /*9*/
            compra = sgvQuemComprouProduto(DEFAULT_PROD, DEFAULT_FIL, sgv);
            filialGetProdutosCliente(compra, N, &bloatTab);
            filialGetProdutosCliente(compra, P, &bloatTab);
            compradoresDestroy(compra);
            /*10*/
            i = sgvGetMaisCompradosCliente(sgv, DEFAULT_CLI, &bloatTab, DEFAULT_MES_HIGH);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            /*11*/
            nComprados = DEAFULT_SIZE;
            fatArr = getMaisVendidos(sgv, &nComprados);
            for(i=0; i < DEAFULT_SIZE; i++){
                for(j=0; j < 3; j++){
                    getQuantMesFilial(fatArr[i], j);
                    sgvQuantosCompraramProdutos(faturaGetId(fatArr[i]), j, sgv);
                }
                destroyFact(fatArr[i]);
            }
            free(fatArr);
            /*12*/
            i = sgvGetMaisVendidosCliente(sgv, DEFAULT_CLI, &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;

        case 2:
            i = getSGVProductLetter(
                sgv,
                (argc == 3 && argv[2][0] >= 'A' && argv[2][0] <= 'Z') ? argv[2][0] : DEFAULT_CHAR,
                &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;

        case 3:
            prod = (argc == 3 && searchSGVProduct(sgv, argv[2]))?argv[2] :  DEFAULT_PROD;
            mes  =    (argc == 4 && atoi(argv[3]))? atoi(argv[3]) : 1;
            for(i = 0; i < 3; i++){
                getFatMesSGV  (sgv, prod, N, i, mes);
                getFatMesSGV  (sgv, prod, P, i, mes);
                getNVendasFat(sgv, prod, N, i, mes);
                getNVendasFat(sgv, prod, P, i, mes);
            }
            break;
        case 4:
            i = prodsNaoComprados(
                sgv,
                (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 3,
                &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;
        case 5:
            i = clientesCompraramFilial(sgv, &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;
        case 6:
            getClientesNCompradores(sgv);
            getProdNComprados(sgv);
            break;
        case 7:
            cli = (argc == 3 && searchSGVClient(sgv, argv[2]))?argv[2] :  DEFAULT_CLI;
            for (i=0; i<3; i++)
                for (j = 0; j < 12; j++)
                    getClientQuantSGV(cli, j, i, sgv);
            break;
        case 8:
            i = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 1;
            j = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : 12;
            getNSalesMes(sgv, i, j);
            getTFactMes(sgv, i, j);
            break;

        case 9:
            compra = sgvQuemComprouProduto(DEFAULT_PROD, DEFAULT_FIL, sgv);
            filialGetProdutosCliente(compra, N, &bloatTab);
            filialGetProdutosCliente(compra, P, &bloatTab);
            compradoresDestroy(compra);
            break;
        case 10:
            i = sgvGetMaisCompradosCliente(
                sgv,
                (argc == 3 && searchSGVClient(sgv, argv[2]))?argv[2] :  DEFAULT_CLI,
                &bloatTab,
                (argc == 4 && atoi(argv[4]))?atoi(argv[4]) : DEFAULT_MES_HIGH);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;
        case 11:
            nComprados = (argc == 3 && atoi(argv[2]) >= 0 && atoi(argv[2]) <= 3) ? atoi(argv[2]) : DEAFULT_SIZE;
            fatArr = getMaisVendidos(sgv, &nComprados); 
            for(i=0; i < nComprados; i++){
                for(j = 0; j < 3; j++){
                    getQuantMesFilial(fatArr[i], j);
                    sgvQuantosCompraramProdutos(faturaGetId(fatArr[i]), j, sgv);
                }
            }
            break;
        case 12:
            i = sgvGetMaisVendidosCliente(
                sgv,
                (argc == 3 && searchSGVClient(sgv, argv[2]))?argv[2] :  DEFAULT_CLI,
                &bloatTab);
            for(j = 0; j < i; j++)
                free(bloatTab[j]);
            free(bloatTab);
            break;
        default:
            break;      
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Answer Query:%f\n", cpu_time_used );
    start = clock();

    destroyInit(init);
    destroySGV(sgv);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr, "CPU Time used to Free structs:%f\n", cpu_time_used );
}
