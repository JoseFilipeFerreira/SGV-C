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

char* getIdProduct(Produto);

void destroyProduct(void*);

#endif
