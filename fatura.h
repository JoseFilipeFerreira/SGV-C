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

FatP cloneFat(FatP a);

double getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes);

int getQuantMesFilial(FatP f, Filial filial);

int getNVendasFatura(FatP f, int mes, Filial filial, Tipo tipo);

void destroyFact(void* f);

int cmpFat(FatP* a, FatP* b);

#endif
