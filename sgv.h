/**
@file sgv.h
@brief Módulo de inicialização de struct
*/
#ifndef ___SGV_H___
#define ___SGV_H___

#include "faturas.h"

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
@brief Obter os Produtos todos

@param sgv Struct com os produtos todos
@return Produtos Produtos todos
*/
Produtos getProdutosTodos(const SGV sgv);

/**
@brief Obter os Clientes todos

@param sgv Struct com os clientes todos
@return Produtos Clientes todos
*/
Clientes getClientesTodos(const SGV sgv);

/**
@brief Define os produtos todos

@param sgv local onde vai ser definido
@param p Produtos todos
*/
void setProdutos(SGV sgv, const Produtos p);

/**
@brief Define os Clientes todos

@param sgv local onde vai ser definido
@param p Produtos todos
*/
void setClientes(SGV sgv, const Clientes p);

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
@param ciente cliente a validar
@return int resultado da aferição
*/
int searchSGVClient(SGV sgv, char* cliente);

double getFatMesSGV(const SGV sgv, const char* produto, Tipo tipo, Filial filial, int mes);

int getQuantFatSGV(const SGV sgv, const char* produto, Tipo tipo, Filial filial, int mes);

int getClientesNCompradores(const SGV sgv);

FatP* getMaisVendidos(const SGV sgv, int N);

int getNVendasFat(const SGV sgv, const char* id, Tipo tipo, Filial filial, int mes);

int getClientQuantSGV(const char* id, int mes, int filial, const SGV sgv);

int sgvQuantosCompraramProdutos(const char* id, int filial, SGV sgv);

int sgvQuemComprouProduto(const char* id, char*** array, SGV sgv);
/**
@brief Libertar um inicializador

@param inicial Inicializador a libertar
*/
void destroyInit(Inicializador inicial);

#endif
