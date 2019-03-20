/**
@file init.h
@brief Módulo de inicialização de struct
*/
#ifndef ___INIT_H___
#define ___INIT_H___

#include "vendas.h"

typedef struct tudo* Tudo;

Tudo tudoInicializadoFilter(const char* pathC, const char* pathP, const char* pathV);

Tudo tudoInicializadoNoFilter(const char* pathC, const char* pathP, const char* pathV);

Produtos getProdutosTodos(const Tudo);

Clientes getClientesTodos(const Tudo);

void setProdutos(Tudo, const Produtos);

void setClientes(Tudo, const Clientes);

void destroyTudo(Tudo);

#endif
