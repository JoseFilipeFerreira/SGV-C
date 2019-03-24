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

/**
@brief Liberta memória alocada para vendas 
*/
void clearSales();

/**
\brief Inicializa a base de dados de vendas, produtos e clientes.

@param filter Indica se é necessário filtrar as vendas, os produtos e os clientes lidos.
@param pathVendas ficheiro onde estão as vendas
@param p produtos todos
@param c clientes todos
*/
int initDB(int filter, char* pathVendas, const Produtos p, const Clientes c);

#endif
