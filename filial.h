/**
@file filial.h
\brief Módulo de tratamento de filiais.
*/
#ifndef ___FILIAL_H___
#define ___FILIAL_H___

#include "venda.h"

/**
 * \brief Estrutura que guarda informacao de uma 
 * filial
 */
typedef struct filiais* Filiais;

/**
 * \brief Estrutura de comunicacao que guarda informacao
 * sobre compradores de um produto
 */
typedef struct compradores* Compradores;

/**
 * \brief Aloca a memoria necessaria para a informacao
 * de uma filial
 *
 * @return Filial com memoria alocada para ser usada
 */
Filiais filialInit();

/**
 * \brief Atualiza ou insere informacao nova numa filial a partir
 * de uma venda
 *
 * @param f Filial a ser atualizada
 * @param v Venda que comporta a informacao a inserir
 * na filial
 */
void filialUpdate(Filiais f, Venda v);

/**
 * \brief Calcula a quantidade de produtos que um cliente
 * comprou num mes
 *
 * Funcao relativa a query 7
 *
 * @param id Id do cliente
 * @param mes Mes das compras
 * @param f Filial a procura
 *
 * @return Quantidade de produtos que um cliente comprou 
 */
int getClientQuant(const char* id, int mes, const Filiais f);

/**
 * \brief Calcula o codigo dos N produtos mais comprados
 * por um cliente
 *
 * O array necessita de ser freed no fim da execucao
 *
 * Funcao relativa a query 12
 *
 * @param f Conjunto de filiais a procurar
 * @param id Codigo do cliente
 * @param N Numero de produtos desejados
 * @param array Array a preencher com os codigos de produto
 *
 * @return Numero de codigs de produto colocados no array
 */
int getMaisVendidosCliente(const Filiais f[], const char* id, int N, char*** array);

/**
 * \brief Calucla a lista de codigos de produtos que um cliente 
 * comprou por ordem decrescente de quantidades
 *
 * O array necessita de ser freed no fim da execucao
 *
 * Funcao relativa a query 10
 *
 * @param f Conjunto de filiais a procurar
 * @param N Numero de filiais
 * @param id Codigo de cliente
 * @param array Array a preencher com os codigos de produto
 * @param mes Mes em qual foram efetuadas as compras
 *
 * @return Numero de codigos de produto colocados no array
 */
int getMaisCompradosCliente(const Filiais f[], int N, const char* id, char*** array, int mes);

/**
 * \brief Calcula quem comprou um produto na filial
 *
 * Funcao relativa a query 9
 *
 * @param f Filial a procurar
 * @param id Id do produto 
 *
 * @return Estrutura com a informacao dos compradores do produto
 */
Compradores produtoQuemComprou(const Filiais f, const char* id);

/**
 * \brief Preenche um array com Ids de cliente presentes na 
 * estrutura Compradores
 *
 * Nao e preciso dar free deste array, pois ja e destruido
 * com a funcao que destroi o Compradores
 *
 * @param c Estrutura com a informacao dos compradores
 * @param t Tipo de venda do qual queremos informacao
 * @param array Array a preencher com os ids
 *
 * @return Numero de ids colocados no array
 */
int filialGetProdutosCliente(Compradores c, Tipo t, char*** array);

/**
 * \brief Calcula o numero de clientes que compraram um produto
 *
 * @param id Id do produto
 * @param f Filial a procurar
 *
 * @return Numero de clientes que compraram o produto
 */
int produtosQuantosCompraram(const char* id, Filiais f);

/**
 * \brief Liberta a memoria ocupada pela estrutura
 *
 * @param c Estrutura a ser limpa
 */
void compradoresDestroy(Compradores c);

/**
 * \brief Liberta a memoria ocupada por uma Filial
 *
 * @param f Filial a destruir
 */
void destroyFilial(Filiais f);
#endif
