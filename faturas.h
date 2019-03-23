/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/
#ifndef ___FATURAS_H___
#define ___FATURAS_H___

#include "fatura.h"

/**
\brief Produtos Lidos.
*/
typedef struct faturas* Faturas;

double getFatTotal(const Faturas p, int mes);

int getQuantTotal(const Faturas p, int mes);

int getProdsVendidos(const Faturas f);

Faturas addFatura(const Venda v, Faturas l);

Faturas initFaturas();

void clearFaturas(Faturas f);

#endif
