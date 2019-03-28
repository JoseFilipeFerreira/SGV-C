#include "queryUI.h"
#include "formating.h"

#include <stdio.h>

char* getValidClientInput(char* header, char* message, char* error, Tudo tudo){
    int r = 0;
    char* initBuf;
    char* buf = malloc(sizeof(char) * 10);
    initBuf = buf;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s --\n" RESET, header);

        if(r)
            printf(UNDER "%s\n\n" RESET, error);
        else
            printf("\n\n");

        printf("%s:\n", message);

        fgets(initBuf, 10, stdin);

        if(searchTudoClient(tudo, strtok(buf, "\n")))
            break;
        else
            r = 1;
    }
    return initBuf;
}

char* getValidProductInput(char* header, char* message, char* error, Tudo tudo){
    int r = 0;
    char* initBuf;
    char* buf = malloc(sizeof(char) * 10);
    initBuf = buf;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s --\n" RESET, header);

        if(r)
            printf(UNDER "%s\n\n" RESET, error);
        else
            printf("\n\n");

        printf("%s:\n", message);

        fgets(initBuf, 10, stdin);

        if(searchTudoProduct(tudo, strtok(buf, "\n")))
            break;
        else
            r = 1;
    }

    return initBuf;
}

int getValidMesInput(char* header, char* message, char* error){
    int mes, r = 0;
    char* initBuf;
    char* buf = malloc(sizeof(char) * 10);
    initBuf = buf;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s --\n" RESET, header);

        if(r)
            printf(UNDER "%s\n\n" RESET, error);
        else
            printf("\n\n");

        printf("%s:\n", message);
        fgets(initBuf, 10, stdin);

        if(strlen(buf) == 0)
            mes = -1;
        else{
            strtok(buf, "\n");
            mes = atoi(buf);
        }

        if(mes > 0 && mes < 13)
            break;
        else
            r = 1;
    }
    free(initBuf);
    return mes;
}

void menuPaginasDraw(char* header, char** tab, int size, int sizePage, int nCols){
    char search;
    int page = 0;
    /*calcular número de páginas*/
    int nPages = (size % (sizePage * nCols))?(size/(sizePage*nCols)) : size/(sizePage*nCols) - 1;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- %s --\n\n" RESET, header);

        printf("Total: %d\n", size);

        printStrings(tab, size, sizePage, nCols, page);

        printf("\t%d/%d [n/p/b]\n", page + 1 , nPages+1);
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

/**
@brief DONE : Query 2
*/
void prodPages(Tudo tudo){
    char search;
    char** prodTab;
    int sizeProdTab;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Produtos/[2] --\n\n" RESET);
        printf("Caracter a pesquisar:\n");
        search = getchar();
        if(search >= 'A' && search <= 'Z')
            break;
    }

    sizeProdTab = getTudoProductLetter(tudo, search, &prodTab);
    menuPaginasDraw("Categoria/Produtos/[2]", prodTab, sizeProdTab,15 , 6);

    free(prodTab);
}

/**
@brief DONE (improve) : Query 3
*/
void prodStatsMes(Tudo tudo){
    int fil, loop = 1;
    char* produto = getValidProductInput(
        "Categoria/Produtos/[3]",
        "Inserir Produto a pesquisar",
        "Produto não existe",
        tudo);

    int mes = getValidMesInput(
        "Categoria/Produtos/[3]",
        "Inserir Mês a pesquisar",
        "Mês inválido"
    );

    while(loop){
        system("clear");
        printf(BOLD KRED "-- Categoria/Produtos/[3] --\n\n"RESET);
        printf("1 - Filial a Filial\n");
        printf("2 - Total\n");

        switch (menuCheck(2))
        {
            case 1:
                system("clear");
                printf(BOLD KRED "-- Categoria/Produtos/[3] --\n\n"RESET);
                printf("Produto: %s\n\n", produto);

                for(fil = 0; fil < 3; fil++){
                    printf("Total faturado no mês %d na filial %d\n", mes, fil + 1);
                    printf("   N: %.2f\n", getFatMesTudo(tudo, produto, N, fil, mes));
                    printf("   P: %.2f\n\n", getFatMesTudo(tudo, produto, P, fil, mes));
                
                    printf("Total comprado no mês %d na filial %d\n", mes, fil + 1);
                    printf("   N: %d\n", getQuantMesTudo(tudo, produto, N, fil, mes));
                    printf("   P: %d\n\n", getQuantMesTudo(tudo, produto, P, fil, mes));
                }

                loop = 0;
                break;
            
            case 2:
                system("clear");
                printf(BOLD KRED "-- Categoria/Produtos/[3] --\n\n"RESET);
                printf("Produto: %s\n\n", produto);

                printf("Total faturado no mês %d\n", mes);
                printf("   N: %.2f\n", getFatMesTudo(tudo, produto, N, ALL, mes));
                printf("   P: %.2f\n\n", getFatMesTudo(tudo, produto, P, ALL, mes));
                
                printf("Número de vendas no mês %d\n", mes);
                printf("   N: %d\n", getQuantMesTudo(tudo, produto, N, ALL, mes));
                printf("   P: %d\n", getQuantMesTudo(tudo, produto, P, ALL, mes));
                
                loop = 0;
                break;
    
            default:
                break;
        }
    }

    printf(HIDE_CURSOR);
    getchar();
    printf(SHOW_CURSOR);
    free(produto);
}

/**
@brief DONE : Query 4
*/
void prodsNCompradosUI(Tudo tudo){
    char** prodTab;
    int sizeProdTab;
    char* initBuf;
    char* buf = malloc(sizeof(char) * 10);
    initBuf = buf;

    int f;

    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Produtos/[4] --\n" RESET);
        printf(BOLD "Produtos não comprados:\n" RESET);
        printf("1 - Filial 1\n");
        printf("2 - Filial 2\n");
        printf("3 - Filial 3\n");
        printf("4 - Todas as Filiais\n");

        fgets(initBuf, 10, stdin);

        f = atoi(strtok(buf, "\n"));

        if(f>0 && f<13)
            break;
    }

    sizeProdTab = prodsNaoComprados(tudo, f-1, &prodTab);
    menuPaginasDraw("Categoria/Produtos/[4]", prodTab, sizeProdTab,15 , 6);

    free(prodTab);
    free(initBuf);

}

/**
@brief DONE : Query 5
*/
void clientesFieis(Tudo tudo){
    char** cliTab;
    int sizeCliTab;

    sizeCliTab = clientesCompraramFilial(tudo, &cliTab);
    menuPaginasDraw("Categoria/Clientes/[5]", cliTab, sizeCliTab,15 , 6);

    free(cliTab);
}

/**
@brief TODO (Prints the result of [2] for testing purposes) : Query 6
*/
void clientesInfieis(Tudo tudo){
    system("clear");
    printf(BOLD KRED"-- Categoria/Clientes/[6] --\n\n"RESET);
    printf("Clientes que não compraram: \n");
    printf("Produtos não comprados:     %d\n", getProdNComprados(tudo));

    printf(HIDE_CURSOR);
    getchar();
    printf(SHOW_CURSOR);
}


/**
@brief TODO : Query 7
*/
void tabClientAno(Tudo tudo, char* cliente){
    int i, j;
    int iT[3][12];
    for (i=0; i<3; i++)
        for (j=0; j<12; j++)
            iT[i][j] = getClientQuantTudo(cliente, j, i, tudo);

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
            3,
            12,
            iT);
}

/**
@brief DONE (improve) : Query 8
*/
void tabVendasIntervalo(Tudo tudo){
    int r = 0;
    int p1, p2;
    char* initBuf;
    char* buf = malloc(sizeof(char) * 10);
    initBuf = buf;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Vendas/[8] --\n" RESET);

        if(r)
            printf(UNDER "Intervalo Inválido\n\n" RESET);
        else
            printf("\n\n");

        printf("Inserir Inicio do intervalo:\n");

        fgets(initBuf, 10, stdin);
        if(strlen(buf) == 0)
            p1 = -1;
        else{
            strtok(buf, "\n");
            p1 = atoi(buf);
        }

        printf("Inserir Fim do intervalo:\n");

        fgets(initBuf, 10, stdin);
        if(strlen(buf) == 0)
            p2 = -1;
        else{
            strtok(buf, "\n");
            p2 = atoi(buf);
        }

        if(p1 > 0 && p1 < 13 && p2 > 0 && p2 < 13 && p1 < p2)
            break;
        else
            r = 1;
    }

    system("clear");
    printf(BOLD KRED "\t-- Categoria/Vendas/[8] --\n\n" RESET);

    printf("Intervalo: %d -> %d\n\n", p1, p2);

    printf("Numero de Vendas %d\n", getNSalesMes(tudo, p1, p2));
    printf("Total Faturado: %.2f\n",  getTFactMes(tudo, p1, p2));

    printf(HIDE_CURSOR);
    getchar();
    printf(SHOW_CURSOR);
    free(buf);
}

/**
@brief TODO : Query 9
*/
void clientesCompraramProduto(Tudo tudo){

}

/**
@brief TODO (Prints the result of [2] for testing purposes) : Query 10
*/
void prodMaisCompradoCli(Tudo tudo){
    int sizeProdTab, mes, r = 0;
    char** prodTab;

    char* initBufMes;
    char* bufMes = malloc(sizeof(char) * 10);
    initBufMes = bufMes;

    char* cliente = getValidClientInput(
        "Categoria/Clientes/[10]",
        "Inserir Cliente a pesquisar",
        "Cliente não existe",
        tudo);

    /* Ler mês válido */
    r = 0;
    while(1){
        system("clear");
        printf(BOLD KRED "\t-- Categoria/Clientes/[10] --\n" RESET);

        if(r)
            printf(UNDER "Mês inválido\n\n" RESET);
        else
            printf("\n\n");

        printf("Inserir Mês a pesquisar:\n");
        fgets(initBufMes, 10, stdin);

        if(strlen(bufMes) == 0)
            mes = -1;
        else{
            strtok(bufMes, "\n");
            mes = atoi(bufMes);
        }

        if(mes > 0 && mes < 13)
            break;
        else
            r = 1;
    }

    sizeProdTab = getTudoProductLetter(tudo, 'A', &prodTab);
    menuPaginasDraw("Categoria/Clientes/[10]", prodTab, sizeProdTab,15 , 6);

    free(cliente);
}

/**
@brief TODO : Query 11
*/
void nMaisComprados(Tudo tudo){

}

/**
@brief TODO : Query 12
*/
void clienteMaisComprados(Tudo tudo, char* cliente){

    printf("\nMais comprados [12]\n");
}

/**
@brief TODO : Query 7 & 12
*/
void statsClientAno(Tudo tudo){
    char* cliente = getValidClientInput(
        "Categoria/Clientes/[7/12]",
        "Inserir Cliente a pesquisar",
        "Cliente não existe",
        tudo);
    
    system("clear");
    printf(BOLD KRED "\t-- Categoria/Clientes/[7/12] --\n\n" RESET);
    printf("Cliente: %s\n\n", cliente);

    tabClientAno(tudo, cliente);
    clienteMaisComprados(tudo, cliente);

    printf(HIDE_CURSOR);
    getchar();
    printf(SHOW_CURSOR);
    free(cliente);
    

}