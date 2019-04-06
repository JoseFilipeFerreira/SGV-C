/**
@file cliente.h
\brief Módulo de tratamento de cliente individual.
*/
#ifndef ___CLIENTE_H___
#define ___CLIENTE_H___

#include <stdbool.h>

/**
@brief Struct para representar a informação de um cliente
*/
typedef struct cliente* Cliente;

/**
@brief Verifica se uma string representa uma cliente valido

@param id string a verificar
@return int se é válido ou não
*/
bool verifyClient(const char* id);

/**
@brief Atualiza o cliente com informacao de onde fez compras

@param c Cliente a atualizar
@param filial Filial onde fez compras
*/
void updateBuyClient(Cliente c, int filial);

/**
@brief Criar uma struct de cliente com base numa string 

@param id string a converter
@return Cliente struct que representa o cliente dado
*/
Cliente mkClient(char* id);

/**
@brief Obter ID de cliente

@param cliente cientes a procurar
@return const char* id do cliente 
*/
char* getIdClient(Cliente cliente);

bool comprouOnde(int filial, Cliente p);

/**
@brief Free de um cliente

@param cliente cliente a libertar
*/
void destroyClient(void* cliente);

#endif
