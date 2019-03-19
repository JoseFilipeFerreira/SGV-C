/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/
#ifndef ___PRODUTOS_H___
#define ___PRODUTOS_H___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "produto.h"

/**
\brief Verifica se um dado produto existe.
*/
Produto searchProduct(const char*);

/**
\brief Devolve o número de produtos armazenados.
*/
int getProductNumber();

int getProductLetter(const char, char***);

void updateProduct(const char*, int, int, int, char, double);

/**
\brief Inicializa a base de dados de produtos.

@param filter Indica se é necessário filtrar os produtos lidos.
@param path ficheiro onde estão os produtos
*/
void initProducts(int filter, const char* path);

void clearProducts();

#endif
