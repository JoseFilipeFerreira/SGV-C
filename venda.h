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

enum Tipo {N, P};
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

char* getClientSale(Venda v); 

char* getProductSale(Venda v); 

int getFilialSale(Venda v); 

enum Tipo getTipoSale(Venda v); 

double getPUnitSale(Venda v); 

int getQuantSale(Venda v); 

int getMesSale(Venda v);

double getTotalSale(Venda v);

/**
@brief Liberta uma Venda 

@param venda Venda a Libertar
*/
void destroySale(Venda venda);

#endif
