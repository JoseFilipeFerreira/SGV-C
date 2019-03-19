#ifndef ___INIT_H___
#define ___INIT_H___

#include "vendas.h"

typedef struct tudo* Tudo;

Tudo tudoInicializado(const char*, const char*, const char*, int);

Produtos getProdutosTodos(const Tudo);

Clientes getClientesTodos(const Tudo);

void destroyTudo(Tudo);

#endif
