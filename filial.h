#ifndef ___FILIAL_H___
#define ___FILIAL_H___

#include "venda.h"

typedef struct filiais* Filiais;

typedef struct compradores* Compradores;

Filiais filialInit();

void filialUpdate(Filiais f, Venda v);

int produQuemComprou(const Filiais f, const char* id, char*** array);

int getClientQuant(const char* id, int mes, const Filiais f);

int getMaisVendidosCliente(const Filiais f[], const char* id, int N, char*** array);

int getMaisCompradosCliente(const Filiais f[], const char* id, int N, char*** array, int mes);

Compradores produtoQuemComprou(const Filiais f, const char* id);

int filialGetProdutosCliente(Compradores c, Tipo t, char*** array);

void compradoresDestroy(Compradores c);
#endif
