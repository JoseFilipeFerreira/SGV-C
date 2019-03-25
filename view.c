#include "view.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sizeInt(int n){
    int i;
    i = (n > 0)?0:1;

    while(n != 0) {
        n /= 10;
        i++;
    }
    return i;
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

void replicate(char* s, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%s", s);
    fflush(stdout);
}

int printStrings(char** s, int ss, int pSize, int nCols, int pN){
    int i, j, pos, r = 0;

    for(i = pSize * pN; i < pSize * (pN + 1); i++){
        for(j = 0; j < nCols && j + i * nCols < ss; j++){
            pos = j + i * nCols;
            printf("%d.", pos + 1);
            replicate(" ", sizeInt(ss) + 1 - sizeInt(pos + 1));
            printf("%s      ", s[pos]);
        }
        r++;
        printf("\n");
    }
    replicate("\n", pSize - r  + 2);
    return r;
}

void printSeparatorLine(int* sizeCols, int col){
    int j;
    for(j=0; j <= col; j++){
        printf("+");
        replicate("-", sizeCols[j]);
    }
    printf("+\n");
}

void printTabela(const char* linLabl[], const char* colLabl[], int** iT, int lin, int col){
    int i, j, lablSize = 0;
    int sizeCols[col+1];
    memset(sizeCols, 0, sizeof(int) * (col + 1));

    /*find apropriate size for colums*/
    for(i = 0; i < lin; i++)
        lablSize = (lablSize < (int)strlen(linLabl[i]))? (int)strlen(linLabl[i]) : lablSize;
    sizeCols[0] = lablSize + 2;
    for(j=0; j < col; j++){
        sizeCols[j + 1] = strlen(colLabl[j]) + 2;
        for(i = 0; i < lin; i ++)
            sizeCols[j+1] = (sizeCols[j+1] < sizeInt(iT[i][j]) + 2)? sizeInt(iT[i][j]) + 2: sizeCols[j+1];
    }

    /*print labl row*/
    printSeparatorLine(sizeCols, col);
    printf("|");
    replicate(" ", sizeCols[0]);
    for(j = 0; j < col; j++){
        printf("| %s", colLabl[j]);
        replicate(" ", sizeCols[j+1] - strlen(colLabl[j]) - 1);
    }
    printf("|\n");
    printSeparatorLine(sizeCols, col);

    for(i = 0; i < lin; i++){
        printf("| %s", linLabl[i]);
        replicate(" ", sizeCols[0] - strlen(linLabl[i]) - 1);
        for(j = 0; j < col; j++){
            printf("| %d", iT[i][j]);
            replicate(" ", sizeCols[j+1] - sizeInt(iT[i][j]) - 1);
        }
        printf("|\n");
        printSeparatorLine(sizeCols, col);
    }
}
