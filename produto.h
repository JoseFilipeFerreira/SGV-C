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

/**
 * \brief Atualiza um dado produto com informacao
 * sobre as filiais onde foi comprado
 *
 * @param p Produto a atualizar
 * @param filial Filial onde foi comprado
 */
void updateCompra(Produto p, int filial);

/**
 * \brief Procura se um produto foi ou nao comprado
 * numa dada filial
 *
 * @param filial Filial onde se quer saber se o
 * produto foi la comprado
 * @param p Produto em questao
 *
 * @return Se o produto foi comprado na filial dada ou nao
 */
bool foiCompradoOnde(int filial, Produto p);

/**
@brief Free de um Produto

@param produto Produto a libertar
*/
void destroyProduct(void* produto);

#endif
