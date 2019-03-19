/**
@file view.h
\brief Módulo de view.
*/
#ifndef ___VIEW_H___
#define ___VIEW_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
@brief Número de caractéres necessários para representar um int

@param n int a analisar
@return int Número de caractéres necessários para o representar
 */
int sizeInt(int n);

/**
@brief Ler input de utilizador

@param size número de itens no menu (máximo de 9)
@return int devolve o id do menu
 */
int menuCheck(int size);

/**
@brief Print a message where \n is default yes

@param message message to show
@return int returns if True or False depending on input
 */
int messageCheck(char* message);

/**
@brief replicate a given string n times

@param s string to duplicate
@param n times to duplicate
 */
void replicate(char* s, int n);

/**
\brief Imprimir lista de strings.

@param s lista de pointers de Strings
@param ss tamanho de s
@param pSize tamanho de cada página
@param pSize tamanho de cada página
@param pN qual é o número da página a desenhar
@param nCols número de colunas
@return Número de strings escritas
*/
int printStrings(char ** s, int ss, int pSize, int nCols, int pN);

/**
@brief Imprimir matriz de int

@param linLabl Rótulos das linhas
@param colLabl Rótulos das colunas
@param iT tabela a imprimir
@param lin número de linhas
@param col número de colunas
 */
void printTabela(const char* linLabl[], const char* colLabl[], int** iT, int lin, int col);

#endif
