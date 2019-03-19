/**
@file io.h
\brief Módulo de user interface.
*/
#ifndef ___IO_H___
#define ___IO_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

/**
\brief Imprimir lista de strings.

@param s lista de pointers de Strings
@param ss tamanho de s
@param pSize tamanho de cada página
@param pN qual é o número da página a desenhar

@return Número de strings escritas
*/
int printStrings(char ** s, int ss, int pSize, int pN);

/**
\brief Cria o menu inicial
*/
void menuInicial();
#endif
