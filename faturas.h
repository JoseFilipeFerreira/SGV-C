/**
@file faturas.h
\brief Módulo de tratamento de faturas.
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

FatP searchFatura(const Faturas f, const char* id);
int getAllList(const Faturas f);
void clearFaturas(Faturas f);

#endif
