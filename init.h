/**
@file init.h
@brief Módulo de inicialização de struct
*/
#ifndef ___INIT_H___
#define ___INIT_H___

#include "faturas.h"

/**
@brief Guardar a base de dados 
*/
typedef struct tudo* Tudo;

/**
@brief Indica como inicializar a base de dados
*/
typedef struct inicializador* Inicializador;

/**
@brief Inicializar a base de dados

@param i Parametros para a leitura
@return Tudo Base de Dados inicializada
*/
Tudo tudoInicializado(Inicializador i);

/**
@brief Obter os Produtos todos

@param tudo Struct com os produtos todos
@return Produtos Produtos todos
*/
Produtos getProdutosTodos(const Tudo tudo);

/**
@brief Obter os Clientes todos

@param tudo Struct com os clientes todos
@return Produtos Clientes todos
*/
Clientes getClientesTodos(const Tudo tudo);

/**
@brief Define os produtos todos

@param tudo local onde vai ser definido
@param p Produtos todos
*/
void setProdutos(Tudo tudo, const Produtos p);

/**
@brief Define os Clientes todos

@param tudo local onde vai ser definido
@param p Produtos todos
*/
void setClientes(Tudo tudo, const Clientes p);

/**
@brief Libertar um Tudo

@param tudo Tudo a libertar
*/
void destroyTudo(Tudo tudo);

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

@param tudo struct que contem tudo
@param inicio inicio da janela temporal
@param fim  fim da janela temporal
@return int número de vendas nessa janela temporal
*/
int getNSalesMes(const Tudo tudo, int inicio, int fim);

/**
@brief Obter o total faturado num periodo de tempo 

@param tudo struct que contem tudo
@param inicio inicio da janela temporal
@param fim  fim da janela temporal
@return int total faturado nessa janela temporal
*/
double getTFactMes(const Tudo tudo, int inicio, int fim);

/**
@brief Número de produtos não comprados

@param tudo struct que contem tudo
@return int Número de produtos não comprados
*/
int getProdNComprados(const Tudo tudo);

int getTudoProductLetter(const Tudo tudo, const char id, char*** array);

/**
@brief calcular a lista de strings de produtos não comprados

@param tudo struct que contem tudo
@param filial filial a procurar
@param array onde guardar o resultado
@return int número de elementos escritos
*/
int prodsNaoComprados(const Tudo tudo, const Filial filial, char*** array);

/**
@brief Afere se um produto é válido ou não

@param tudo struct que contem tudo
@param produto produto a validar
@return int resultado da aferição
*/
int searchTudoProduct(Tudo tudo, char* produto);

/**
@brief Afere se um cliente é válido ou não

@param tudo struct que contem tudo
@param ciente cliente a validar
@return int resultado da aferição
*/
int searchTudoClient(Tudo tudo, char* cliente);

double getFatMesTudo(const Tudo tudo, const char* produto, Tipo tipo, Filial filial, int mes);

int getQuantMesTudo(const Tudo tudo, const char* produto, Tipo tipo, Filial filial, int mes);

int getClientesNCompradores(const Tudo tudo);

/**
@brief Libertar um inicializador

@param inicial Inicializador a libertar
*/
void destroyInit(Inicializador inicial);

#endif
