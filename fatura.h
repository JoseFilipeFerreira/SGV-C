/**
@file fatura.h
\brief Módulo de tratamento de fatura individual.
*/
#ifndef ___FATURA_H___
#define ___FATURA_H___

#include "venda.h"

/**
 * \brief Struct que guarda informacao de compras de um produto
 */
typedef struct faturacaoProd* FatP;

/**
 * \brief Inicializa uma FatP
 *
 * @param v Venda com informacao para criar a FatP
 *
 * @return FatP criada e atualizada
 */
FatP initFatP(Venda v);

/**
 * \brief Atualiza uma FatP com informacao de uma venda
 *
 * @param fat FatP a atualizar
 * @param v Venda com a informacao a atualizar
 */
void mkFatura(FatP fat, Venda v);

/**
 * \brief Clona uma FatP
 *
 * @param a FatP a clonar
 *
 * @return FatP clonada
 */
FatP cloneFat(FatP a);

/**
 * \brief Calcula o total faturado num produto
 *
 * @param f FatP a calcular o total faturado
 * @param tipo Tipo de venda do qual se pretende saber o total
 * faturado
 * @param filial Filial onde foram efetuadas as compras
 * @param mes Mes em que foram efetuadas as compras
 *
 * @return Total faturado conforme os parametros
 */
double getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes);

/**
 * \brief Calcula o total de unidades compradas de um produto
 *
 * @param f FatP referente ao produto
 * @param filial Filial onde foram feitas as vendas
 *
 * @return Numero de produtos vendidos
 */
int getQuantMesFilial(FatP f, Filial filial);

/**
 * \brief Calcula o numero de vendas efetuadas de um produto
 *
 * @param f FatP referente ao produto
 * @param mes Mes em que foram efetuadas as vendas
 * @param filial Filial onde foram efetuadas as vendas
 * @param tipo Tipo de venda
 *
 * @return Numero de vendas do produto conforme os parametros
 */
int getNVendasFatura(FatP f, int mes, Filial filial, Tipo tipo);

/**
 * \brief Destroi uma fatura dando free da memoria
 * alocada
 *
 * @param f FatP a destruir
 */
void destroyFact(void* f);

/**
 * \brief Getter do Id de uma FatP
 *
 * @param f FatP que se pretende devolver o id
 *
 * @return Id da FatP
 */
char* faturaGetId(const FatP f);

/**
 * \brief Compara duas faturas relativamente as quantidades vendidas
 *
 * @param a Primeira fatura a comparar
 * @param b segunda fatura a comparar
 *
 * @return Maior, menor ou igual a 0, caso as quantidades de b sejam
 * maiores, menores ou iguais as de a, respetivamente
 */
int cmpFat(const void* a, const void* b);

#endif
