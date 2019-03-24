/**
@file fatura.h
\brief Módulo de tratamento de fatura individual.
*/
#ifndef ___FATURA_H___
#define ___FATURA_H___

#include "venda.h"

typedef struct faturacaoProd* FatP;

FatP initFatP(Venda v);

void mkFatura(FatP fat, Venda v);

int getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes);

int getQuantMesFilial(FatP f, Tipo tipo, Filial filial, int mes);

void destroyFact(void* f);

#endif
