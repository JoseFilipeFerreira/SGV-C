/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/

#ifndef ___PRODUTOS_H___
#define ___PRODUTOS_H___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
\brief Verifica se um dado produto existe.
*/
int* searchProduct(char*);

/**
\brief Devolve o número de produtos armazenados.
*/
int getProductNumber();

/**
\brief Inicializa a base de dados de produtos.

@param filter Indica se é necessário filtrar os produtos lidos.
*/
void initProducts(int filter);

#endif
