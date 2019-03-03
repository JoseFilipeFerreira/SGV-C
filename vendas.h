/**
@file vendas.h
\brief Módulo de tratamento de vendas.
*/

#ifndef ___VENDAS_H___
#define ___VENDAS_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "vendas.h"

/**
\brief Devolve o número de vendas armazenadas.
*/
int getSalesNumber();

/**
\brief Inicializa a base de dados de vendas, produtos e clientes.

@param filter Indica se é necessário filtrar as vendas, os produtos e os clientes lidos.
*/
void initDB(int filter);

#endif
