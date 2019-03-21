/**
@file venda.h
\brief Módulo de tratamento de venda individual.
*/
#ifndef ___VENDA_H___
#define ___VENDA_H___

#include "produtos.h"
#include "clientes.h"

/**
\brief Estrutura para guardar uma venda.
*/
typedef struct venda* Venda;

/**
@brief Verifica se uma dada String representa uma Venda Válida

@param sale String a avaliar
@param p Produtos todos
@param c Clientes todos
@return int Se é válida ou não
*/
int verifySale(const char* sale, const Produtos p, const Clientes c);

/**
@brief Gera uma Venda com base numa string

@param sale String a converter
@return Venda Struct que representa a venda dada
*/
Venda mkSale(const char* sale);

/**
@brief Liberta uma Venda 

@param venda Venda a Libertar
*/
void destroySale(Venda venda);

#endif
