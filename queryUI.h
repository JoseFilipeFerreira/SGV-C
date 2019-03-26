/**
@file queryUI.h
@brief Módulo de menus específicos para query
*/
#ifndef ___QUERYUI_H___
#define ___QUERYUI_H___

#include "view.h"
#include "init.h"

/**
@brief Query 2

@param tudo struct que conte a base de dados
*/
void prodPages(Tudo tudo);

/**
@brief Query 3

@param tudo struct que conte a base de dados
*/
void prodStatsMes(Tudo tudo);

/**
@brief Query 4

@param tudo struct que conte a base de dados
*/
void prodsNCompradosUI(Tudo tudo);

/**
@brief Query 5

@param tudo struct que conte a base de dados
*/
void clientesFieis(Tudo tudo);

/**
@brief Query 6

@param tudo struct que conte a base de dados
*/
void clientesInfieis(Tudo tudo);

/**
@brief Query 8

@param tudo struct que conte a base de dados
*/
void tabVendasIntervalo(Tudo tudo);

/**
@brief Query 9

@param tudo struct que conte a base de dados
*/
void clientesCompraramProduto(Tudo tudo);

/**
@brief Query 10

@param tudo struct que conte a base de dados
*/
void prodMaisCompradoCli(Tudo tudo);

/**
@brief TODO : Query 11

@param tudo struct que conte a base de dados
*/
void nMaisComprados(Tudo tudo);

/**
@brief Query 7 & 12

@param tudo struct que conte a base de dados
*/
void statsClientAno(Tudo tudo);

#endif
