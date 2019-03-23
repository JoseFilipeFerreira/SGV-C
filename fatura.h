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

char* getProdFact(FatP f);

char getTipoFact(FatP f);

double getPUnitFact(FatP f);

int getQuantFact(FatP f);

int getTotalFact(FatP f);

void destroyFact(void* f);

#endif
