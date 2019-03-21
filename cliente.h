/**
@file cliente.h
\brief Módulo de tratamento de cliente individual.
*/
#ifndef ___CLIENTE_H___
#define ___CLIENTE_H___

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cliente* Cliente;

int verifyClient(const char*);

Cliente mkClient(char*);

char* getIdClient(Cliente);

void destroyClient(void*);

#endif
