/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/
#ifndef ___PRODUTOS_H___
#define ___PRODUTOS_H___

#include "glibW.h"
#include "produto.h"

typedef struct produtos* Produtos;

/**
\brief Verifica se um dado produto existe.
*/
int searchProduct(const Produtos, const char*);

/**
\brief Devolve o número de produtos armazenados.
*/
int getProductNumber(const Produtos);

int getProductLetter(const Produtos, const char, char***);

void updateProduct(const char*, int, int, int, char, double);

Produtos addProduct(const Produto, Produtos);

Produtos initProducts();

void clearProducts(Produtos);

#endif
