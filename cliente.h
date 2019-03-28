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
@brief Verifica se uma string representa uma string

@param id string a verificar
@return int se é válido ou não
*/
bool verifyClient(const char* id);

void updateBuyClient(Cliente c, int filial, int mes, int quantidade);

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

int getClientQuantidades(const Cliente c, int mes, int filial);

/**
@brief Free de um cliente

@param cliente cliente a libertar
*/
void destroyClient(void* cliente);

#endif
