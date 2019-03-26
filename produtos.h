/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/
#ifndef ___PRODUTOS_H___
#define ___PRODUTOS_H___

#include "glibW.h"
#include "produto.h"

/**
\brief Produtos Lidos.
*/
typedef struct produtos* Produtos;

/**
@brief Verifica se um dado produto existe.

@param p Produtos todos
@param id Id a aferir a existência
@return int Se existe ou não 
*/
bool searchProduct(const Produtos p, const char* id);

/**
@brief Devolve o número de produtos armazenados

@param p Produtos todos 
@return int Número de produtos armazenados
*/
int getProductNumber(const Produtos p);

/**
@brief Obter o array de strings de Produtoscomeçadas por uma letra

@param p Todos os Produtos
@param id O primeiro caracter
@param array Onde vão ser guardadas as strings
@return int Número de Produtos com o caracter
*/
int getProductLetter(const Produtos p, const char id, char*** array);

/**
@brief Adicionar um produto

@param p produto a adicionar
@param l onde adicionar
@return Produtos produto adicionado
*/
Produtos addProduct(const Produto p, Produtos l);

/**
@brief Alocar espaço para os produtos

@return Produtos Produtos alocados
*/
Produtos initProducts();

int getNaoComprados(const Produtos p, int filial, char*** array);

void produtosUpdateCompra(const char* id, int filial, Produtos r);
/**
@brief Libertar espaço alocado para Produtos

@param p Produtos a libertar
*/
void clearProducts(Produtos p);

#endif
