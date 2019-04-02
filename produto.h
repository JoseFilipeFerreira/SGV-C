/**
@file produto.h
\brief Módulo de tratamento de produto individual.
*/
#ifndef ___PRODUTO_H___
#define ___PRODUTO_H___

#include <stdbool.h>

/**
@brief Struct para representar a informação de um produto
*/
typedef struct produto* Produto;

/**
@brief Verifica se uma string representa um Produto

@param id String a verificar
@return int Se representa ou não um produto
*/
bool verifyProduct(const char* id);

/**
@brief Criar uma struct de produto com base numa string 

@param id string a converter
@return Produto struct que representa o produto dado
*/
Produto mkProduct(char* id);

/**
@brief Obter ID de produto

@param produto produto a procurar
@return const char* id do produto
*/
char* getIdProduct(Produto produto);

void updateCompra(Produto p, int filial);

bool foiCompradoOnde(int filial, Produto p);

int produtoQuantosCompraram(int filial, Produto p); 

void produtoAddQuemComprou(int filial, char* id, Produto p); 
/**
@brief Free de um Produto

@param produto Produto a libertar
*/
void destroyProduct(void* produto);

#endif
