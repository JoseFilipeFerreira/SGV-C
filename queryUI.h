/**
@file queryUI.h
@brief Módulo de menus específicos para query
*/
#ifndef ___QUERYUI_H___
#define ___QUERYUI_H___

#include "view.h"
#include "sgv.h"

/**
@brief Query 2

@param sgv struct que conte a base de dados
*/
void prodPages(SGV sgv);

/**
@brief Query 3

@param sgv struct que conte a base de dados
*/
void prodStatsMes(SGV sgv);

/**
@brief Query 4

@param sgv struct que conte a base de dados
*/
void prodsNCompradosUI(SGV sgv);

/**
@brief Query 5

@param sgv struct que conte a base de dados
*/
void clientesFieis(SGV sgv);

/**
@brief Query 6

@param sgv struct que conte a base de dados
*/
void clientesInfieis(SGV sgv);

/**
@brief Query 8

@param sgv struct que conte a base de dados
*/
void tabVendasIntervalo(SGV sgv);

/**
@brief Query 9

@param sgv struct que conte a base de dados
*/
void clientesCompraramProduto(SGV sgv);

/**
@brief Query 10

@param sgv struct que conte a base de dados
*/
void prodMaisCompradoCli(SGV sgv);

/**
@brief TODO : Query 11

@param sgv struct que conte a base de dados
*/
void nMaisComprados(SGV sgv);

/**
@brief Query 7 & 12

@param sgv struct que conte a base de dados
*/
void statsClientAno(SGV sgv);

#endif
