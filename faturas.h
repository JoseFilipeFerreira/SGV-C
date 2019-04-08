/**
@file faturas.h
\brief Módulo de tratamento de faturas.
*/
#ifndef ___FATURAS_H___
#define ___FATURAS_H___

#include "fatura.h"

/**
\brief Produtos Lidos.
*/
typedef struct faturas* Faturas;

/**
 * @brief Calcula o total faturado num mês
 * 
 * @param p Estrutura que contém as faturas
 * @param mes Mes a procurar
 * @return double Total faturado no dado mês
 */
double getFatTotal(const Faturas p, int mes);

/**
 * @brief Calcula a quantidade total vendida num mês
 * 
 * @param p Estrutura que contém as faturas
 * @param mes Mes a procurar
 * @return double Quantidade total no dado mês
 */
int getQuantTotal(const Faturas p, int mes);

/**
 * @brief Calcula o número de produtos individuais vendidos
 * 
 * @param f Estrutura que contém as faturas
 * @return int Número de produtos individuais vendidos
 */
int getProdsVendidos(const Faturas f);

/**
 * @brief Adiciona uma dada fatura
 * 
 * @param v Venda com a informação a adicionar à estrutura
 * @param l Estrutura a atualizar
 */
void addFatura(const Venda v, Faturas l);

/**
 * @brief Inicializa e aloca memória para a estrutura de Faturação
 * 
 * @return Faturas Estrutura de faturação inicializada
 */
Faturas initFaturas();

/**
 * @brief Procura a fatura respetiva de um dado produto
 * 
 * @param f Faturas onde se encontram os dados a procurar
 * @param id Id do produto
 * @return FatP Fatura requesitada
 */
FatP searchFatura(const Faturas f, const char* id);

/**
 * @brief Cria um array com todas as faturas
 * 
 * @param f Estrutura com as faturas
 * @param N Tamanho do array de retorno
 * @return FatP* Array com o clone de todas as Faturas
 */
FatP* getAllList(const Faturas f, int* N);

/**
 * @brief Calcula o número de vendas de um determinado produto
 * 
 * @param f Estrutura com a Faturação
 * @param id Id do produto
 * @param mes Mês onde foram efetuadas as vendas
 * @param filial Filial onde foram efetuadas as vendas
 * @param tipo Tipo de venda a procurar
 * @return int Total de vendas efetuadas para um dado produto
 */
int getNVendasFaturas(const Faturas f, const char* id, int mes, Filial filial, Tipo tipo);

/**
 * @brief Liberta a memória alocada para a estrutura de Faturação
 * 
 * @param f Estrutura de faturação a destruir
 */
void clearFaturas(Faturas f);

#endif
