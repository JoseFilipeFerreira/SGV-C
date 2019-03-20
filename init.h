/**
@file init.h
@brief Módulo de inicialização de struct
*/
#ifndef ___INIT_H___
#define ___INIT_H___

#include "vendas.h"

typedef struct tudo* Tudo;

typedef struct inicializador* Inicializador;

Tudo tudoInicializado(Inicializador);

Produtos getProdutosTodos(const Tudo);

Clientes getClientesTodos(const Tudo);

void setProdutos(Tudo, const Produtos);

void setClientes(Tudo, const Clientes);

void destroyTudo(Tudo);

Inicializador initInicial();

int getLinesProducts(const Inicializador i);

int getLinesSales(const Inicializador i);

int getLinesClients(const Inicializador i);

void setClientPath(Inicializador i, const char* p, int f);

void setProductPath(Inicializador i, const char* p, int f);

void setSalePath(Inicializador i, const char* p, int f);

int getNumberClients(const Inicializador i);

int getNumberProducts(const Inicializador i);

int getNumberSales(const Inicializador i);

char* getSalePath(const Inicializador i);

char* getProductPath(const Inicializador i);

char* getClientPath(const Inicializador i);

void destroyInit(Inicializador inicial);

#endif
