/**
@file sgv.h
@brief Módulo de inicialização de struct
*/
#ifndef ___SGV_H___
#define ___SGV_H___

#include "faturas.h"
#include "filial.h"

/**
@brief Guardar a base de dados 
*/
typedef struct sgv* SGV;

/**
@brief Indica como inicializar a base de dados
*/
typedef struct inicializador* Inicializador;

/**
@brief Inicializar a base de dados

@param i Parametros para a leitura
@return SGV Base de Dados inicializada
*/
SGV sgvInicializado(Inicializador i);

/**
@brief Libertar um SGV

@param sgv SGV a libertar
*/
void destroySGV(SGV sgv);

/**
@brief Alocar espaço para um Inicializador

@return Inicializador Inicializador alocado
*/
Inicializador initInicial();

/**
@brief Quantidade de produtos lidos

@param i Struct Inicializador
@return int Número de linhas lidas
*/
int getLinesProducts(const Inicializador i);

/**
@brief Quantidade de vendas lidas

@param i Struct Inicializador
@return int Número de linhas lidas
*/
int getLinesSales(const Inicializador i);

/**
@brief Quantidade de clientes lidos

@param i Struct Inicializador
@return int Número de linhas lidas
*/
int getLinesClients(const Inicializador i);


/**
@brief Definir como ler os Clientes

@param i Inicializador a alterar
@param p Caminho para o Ficheiro
@param f Filtrar o ficheiro ou não
*/
void setClientPath(Inicializador i, const char* p, int f);

/**
@brief Definir como ler os Produtos

@param i Inicializador a alterar
@param p Caminho para o Ficheiro
@param f Filtrar o ficheiro ou não
*/
void setProductPath(Inicializador i, const char* p, int f);

/**
@brief Definir como ler as Vendas

@param i Inicializador a alterar
@param p Caminho para o Ficheiro
@param f Filtrar o ficheiro ou não
*/
void setSalePath(Inicializador i, const char* p, int f);

/**
@brief Quantidade de clientes válidos lidos

@param i Struct Inicializador
@return int Número de linhas válidas lidas
*/
int getNumberClients(const Inicializador i);

/**
@brief Quantidade de pródutos válidos lidos

@param i Struct Inicializador
@return int Número de linhas válidas lidas
*/
int getNumberProducts(const Inicializador i);

/**
@brief Quantidade de vendas válidas lidas

@param i Struct Inicializador
@return int Número de linhas válidas lidas
*/
int getNumberSales(const Inicializador i);

/**
@brief Obter o caminho para o ficheiro de vendas

@param i Struct Inicializador
@return char* Caminho para o ficheiro
*/
char* getSalePath(const Inicializador i);

/**
@brief Obter o caminho para o ficheiro de produtos

@param i Struct Inicializador
@return char* Caminho para o ficheiro
*/
char* getProductPath(const Inicializador i);

/**
@brief Obter o caminho para o ficheiro de clientes

@param i Struct Inicializador
@return char* Caminho para o ficheiro
*/
char* getClientPath(const Inicializador i);

/**
@brief Obter o número de vendas num periodo de tempo 

@param sgv struct que contem sgv
@param inicio inicio da janela temporal
@param fim  fim da janela temporal
@return int número de vendas nessa janela temporal
*/
int getNSalesMes(const SGV sgv, int inicio, int fim);

/**
@brief Obter o total faturado num periodo de tempo 

@param sgv struct que contem sgv
@param inicio inicio da janela temporal
@param fim  fim da janela temporal
@return int total faturado nessa janela temporal
*/
double getTFactMes(const SGV sgv, int inicio, int fim);

/**
@brief Número de produtos não comprados

@param sgv struct que contem sgv
@return int Número de produtos não comprados
*/
int getProdNComprados(const SGV sgv);

/**
 * \brief Obtem a lista de produtos cujo id começa por uma determinada letra
 *
 * Função relativa à query 2
 *
 * É necessário fazer free dos elementos do array
 *
 * @param sgv Struct que contem o sgv
 * @param id Letra que pretendemos procurar
 * @param array Array a preencher com os ids dos produtos obtidos
 *
 * @return Número de produtos começados com a letra dada
 */
int getSGVProductLetter(const SGV sgv, const char id, char*** array);

/**
@brief calcular a lista de strings de produtos não comprados

@param sgv struct que contem sgv
@param filial filial a procurar
@param array onde guardar o resultado
@return int número de elementos escritos
*/
int prodsNaoComprados(const SGV sgv, const Filial filial, char*** array);

/**
@brief Afere se um produto é válido ou não

@param sgv struct que contem sgv
@param produto produto a validar
@return int resultado da aferição
*/
int searchSGVProduct(SGV sgv, char* produto);

/**
@brief Afere se um cliente é válido ou não

@param sgv struct que contem sgv
@param cliente cliente a validar
@return int resultado da aferição
*/
int searchSGVClient(SGV sgv, char* cliente);

/**
 * \brief Calcula o total faturado de um produto num mês 
 *
 * @param sgv SGV com a informação da faturação
 * @param produto Id do produto a pesquisar
 * @param tipo Tipo de venda do qual pretendemos a faturação
 * @param filial Filial onde foram efetuadas as vendas
 * @param mes Mês onde foram efetuadas as vendas
 *
 * @return Total faturado por um produto conforme os parametros dados
 */
double getFatMesSGV(const SGV sgv, const char* produto, Tipo tipo, Filial filial, int mes);

/**
 * \brief Calcula o número de clientes que não efetuaram compras
 *
 * @param sgv SGV com a informação dos clientes
 *
 * @return Número de clientes que nunca fizeram compras
 */
int getClientesNCompradores(const SGV sgv);

/**
 * \brief Determina a lista de produtos mais vendidos, ordenados por ordem
 * decrescente
 *
 * É necessário fazer free dos elementos do array de return
 *
 * @param sgv SGV com a informação da faturação
 * @param N Tamanho do array de return
 *
 * @return Lista de Faturas ordenadas
 */
FatP* getMaisVendidos(const SGV sgv, int* N);

/**
 * \brief Calcula o número de vendas num mês de um produto
 *
 * @param sgv SGV com a informação da faturação
 * @param id Id do produto a procurar
 * @param tipo Tipo de venda do qual pretendemos o número de vendas
 * @param filial Filial onde foram efetuadas as vendas
 * @param mes Mês onde foram feitas as vendas
 *
 * @return Total de vendas do produto dado conforme os parametros
 */
int getNVendasFat(const SGV sgv, const char* id, Tipo tipo, Filial filial, int mes);

/**
 * \brief Calcula o número total de produtos comprados por um cliente
 *
 * @param id Id do cliente em questão
 * @param mes Mês onde foram efetuadas as compras
 * @param filial Filial onde o cliente fez as compras
 * @param sgv SGV com a informação da faturação e filiais
 *
 * @return Número de produtos que o cliente em questão fez conforme os 
 * parametros
 */
int getClientQuantSGV(const char* id, int mes, int filial, const SGV sgv);

/**
 * \brief Calcula o número de clientes que compraram um determinado produto
 *
 * @param id Produto a pesquisar
 * @param filial Filial onde o produto foi vendido
 * @param sgv SGV com a informação das filias
 * 
 * @return Número de clientes que compraram o produto na filial dada
 */
int sgvQuantosCompraramProdutos(const char* id, int filial, SGV sgv);

/**
 * \brief Determina a lista de quem comprou um produto, separado por tipo de
 * venda
 *
 * @param id Produto a pesquisar
 * @param f Filial onde foram feitas as compras
 * @param sgv SGV com a informação das filiais
 *
 * @return Estrutura com a informação de quem comprou o produto na filial dada
 */
Compradores sgvQuemComprouProduto(const char* id, Filial f, SGV sgv);

/**
 * \brief Calcula os três produtos onde um cliente gastou mais dinheiro
 *
 * @param sgv SGV com a informação das filiais
 * @param id Id do cliente em questão
 * @param array Array a preencher com os ids de produtos
 *
 * @return Número de produtos inseridos no array dado
 */
int sgvGetMaisVendidosCliente(const SGV sgv, const char* id, char*** array);

/**
 * \brief Calcula a lista ordenada de produtos mais comprados por um cliente
 *
 * @param sgv SGV com a informação das filiais
 * @param id Id do cliente em questão
 * @param array Array a preencher com os ids de produtos
 * @param mes Mês onde foram efetuadas as compras
 *
 * @return Número de produtos inseridos no array dado
 */
int sgvGetMaisCompradosCliente(const SGV sgv, const char* id, char*** array, int mes);

/**
 * \brief Determina a lista dos clientes que compraram em todas as filiais
 *
 * @param sgv SGV com a informação de clientes
 * @param array Array a preencher com os ids de clientes
 *
 * @return Número de clientes inseridos no array dado
 */
int clientesCompraramFilial (const SGV sgv, char*** array);

/**
@brief Libertar um inicializador

@param inicial Inicializador a libertar
*/
void destroyInit(Inicializador inicial);

#endif
