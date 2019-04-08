/**
@file venda.h
\brief Módulo de tratamento de venda individual.
*/
#ifndef ___VENDA_H___
#define ___VENDA_H___

#include "produtos.h"
#include "clientes.h"

/**
\brief Estrutura para guardar uma venda
*/
typedef struct venda* Venda;

/**
@brief Representação da filial a pesquisar
*/
typedef enum filial {A, B, C, ALL} Filial;

/**
 * @brief Representação do tipo de venda a pesquisar
 */
typedef enum tipo {N, P, AL} Tipo;

/**
@brief Verifica se uma dada String representa uma Venda Válida

@param sale String a avaliar
@param p Produtos todos
@param c Clientes todos
@return int Se é válida ou não
*/
int verifySale(const char* sale, const Produtos p, const Clientes c);

/**
@brief Gera uma Venda com base numa string

@param sale String a converter
@return Venda Struct que representa a venda dada
*/
Venda mkSale(const char* sale);

/**
 * @brief Procura o Id do cliente da venda
 * 
 * @param v Venda a procurar
 * @return char* Id do cliente
 */
char* getClientSale(Venda v); 

/**
 * @brief Procura o Id do produto da venda
 * 
 * @param v Venda a procurar
 * @return char* Id do produto
 */
char* getProductSale(Venda v); 

/**
 * @brief Procura a filial da venda
 * 
 * @param v Venda a procurar
 * @return Filial filial da venda
 */
Filial getFilialSale(Venda v);

/**
 * @brief Procura o tipo da venda
 * 
 * @param v Venda a procurar
 * @return Tipo Tipo da venda
 */
Tipo getTipoSale(Venda v); 

/**
 * @brief Calcula o preço unitário do produto vendido
 * 
 * @param v Venda a procurar
 * @return double preço unitário do produto vendido
 */
double getPUnitSale(Venda v); 

/**
 * @brief Calcula a quantidade de produtos vendidos
 * 
 * @param v Venda a procurar
 * @return int quantidade de produtos vendidos
 */
int getQuantSale(Venda v); 

/**
 * @brief Obtém o mês em que a venda foi efetuada
 * 
 * @param v Venda a procurar
 * @return int Mes da venda
 */
int getMesSale(Venda v);

/**
 * @brief Calcula a faturação total da venda
 * 
 * @param v Venda a procurar
 * @return double Faturação total da venda
 */
double getTotalSale(Venda v);

/**
@brief Liberta uma Venda 

@param venda Venda a Libertar
*/
void destroySale(Venda venda);

#endif
