/**
@file vendas.h
\brief Módulo de tratamento de vendas.
*/

#ifndef ___VENDAS_H___
#define ___VENDAS_H___

#include "venda.h"

/**
\brief Devolve o número de vendas armazenadas.
*/
int getSalesNumber();

void clearSales();

/**
\brief Inicializa a base de dados de vendas, produtos e clientes.

@param filter Indica se é necessário filtrar as vendas, os produtos e os clientes lidos.
@param pathProdutos ficheiro onde estão os produtos
@param pathClientes ficheiro onde estão os clientes
@param pathVendas ficheiro onde estão as vendas
*/
int initDB(int, char*, const Produtos, const Clientes);

#endif
