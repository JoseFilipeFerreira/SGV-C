/**
@file clientes.h
\brief Módulo de tratamento de clientes.
*/
#ifndef ___CLIENTES_H___
#define ___CLIENTES_H___

#include <glib.h>
#include "cliente.h"

typedef struct clientes* Clientes;

/**
\brief Verifica se um dado cliente existe.
*/
int searchClient(const Clientes, const char*);

/**
\brief Devolve o número de clientes armazenados.
*/
int getClientNumber(const Clientes);

int getClientLetter(const Clientes, const char, char***);

void updateClient(const char*, int, int, int, char, double);

Clientes initClients();

void clearClients(Clientes);

#endif
