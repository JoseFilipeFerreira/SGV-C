/**
@file queryUI.h
@brief Módulo de menus específicos para query
*/
#ifndef ___QUERYUI_H___
#define ___QUERYUI_H___

#include "formating.h"
#include "view.h"
#include "init.h"
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

/**
@brief Query 2
*/
void prodPages(Tudo tudo);

/**
@brief Query 3
*/
void prodStatsMes(Tudo tudo);

/**
@brief Query 5
*/
void clientesFieis(Tudo tudo);

/**
  @brief Query 7
  */
void tabClientAno(Tudo tudo);

/**
@brief Query 8
*/
void tabVendasIntervalo(Tudo tudo);

/**
@brief Query 10
*/
void prodMaisCompradoCli(Tudo tudo);

#endif
