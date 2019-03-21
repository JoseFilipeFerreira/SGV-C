/**
@file clientes.h
\brief Módulo de tratamento de clientes.
*/
#ifndef ___CLIENTES_H___
#define ___CLIENTES_H___

#include "glibW.h"
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

Clientes addClient(const Cliente, Clientes);

void clearClients(Clientes);

#endif
