/**
@file venda.h
\brief Módulo de tratamento de venda individual.
*/
#ifndef ___VENDA_H___
#define ___VENDA_H___

#include "produtos.h"
#include "clientes.h"

typedef struct venda* Venda;

int verifySale(const char*, const Produtos, const Clientes);

Venda mkSale(const char*);

void destroySale(Venda);

#endif
