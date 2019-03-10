/**
@file clientes.h
\brief Módulo de tratamento de clientes.
*/

#ifndef ___CLIENTES_H___
#define ___CLIENTES_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
\brief Verifica se um dado cliente existe.
*/
int* searchClient(char*);

/**
\brief Devolve o número de clientes armazenados.
*/
int getClientNumber();

/**
\brief Devolve o número de clientes cujo ID comece pela letra dada.
*/
int getClientLetter(char);

/**
\brief Inicializa a base de dados de clientes.

@param filter Indica se é necessário filtrar os clientes lidos.
*/
void initClients(int filter);


#endif
