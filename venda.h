/**
@file venda.h
\brief Módulo de tratamento de venda individual.
*/
#ifndef ___VENDA_H___
#define ___VENDA_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "clientes.h"
#include <glib.h>

typedef struct venda* Venda;

int verifySale(const char*);

Venda mkSale(const char*);

void destroySale(Venda);

#endif
