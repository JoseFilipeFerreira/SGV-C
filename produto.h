/**
@file produto.h
\brief Módulo de tratamento de produto individual.
*/
#ifndef ___PRODUTO_H___
#define ___PRODUTO_H___

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto* Produto;

int verifyProduct(const char*);

Produto mkProduct(char*);

void addFactProduct(Produto, int, int, int, double, char);

void addQuantProduct(Produto, int, int, int);

void addSaleNumber(Produto, int, int);

const char* getIdProduct(Produto);

void destroyProduct(Produto);

void printProduct(Produto);

#endif
