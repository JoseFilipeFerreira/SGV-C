/**
@file clientes.h
\brief Módulo de tratamento de clientes.
*/
#ifndef ___CLIENTES_H___
#define ___CLIENTES_H___

#include "glibW.h"
#include "cliente.h"

/**
\brief Clientes Lidos.
*/
typedef struct clientes* Clientes;

/**
@brief Verifica se um dado cliente existe.

@param p Todos os clientes
@param id String a procurar
@return int Devolve se existe
*/
int searchClient(const Clientes p, const char* id);

/**
 * @brief Devolve o número de clientes armazenados.
 * 
 * @param p Todos os clientes
 * @return int Devolve o número de clientes
 */
int getClientNumber(const Clientes p);

int getComprador(const Clientes p, char*** array);
/**
@brief Obter o array de strings de Cliente começadas por uma letra

@param p Todos os clientes
@param id O primeiro caracter
@param array Onde vão ser guardadas as strings
@return int Número de clientes com o caracter
*/
int getClientLetter(const Clientes p, const char id, char*** array);

/**
@brief Inicializar os clientes todos

@return Clientes Struct com memória alocada
*/
Clientes initClients();

/**
@brief Adicionar um cliente

@param p cliente a adicionar
@param l onde adicionar
@return Clientes Clientes editados
*/
Clientes addClient(const Cliente p, Clientes l);

void clientesUpdateCompra(const char* id, int filial, int mes, int quant, Clientes r);

int getClientesNaoCompradores(const Clientes p);

int getClientQuant(const char* id, int mes, int filial, const Clientes c);

/**
@brief Libertar uma struct de clientes

@param p struct a libertar
*/
void clearClients(Clientes p);

#endif
