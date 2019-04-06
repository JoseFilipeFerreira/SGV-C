#include "faturas.h"

/**
  @brief Número de Letras no alfabeto
  */
#define LETTERS 26

/**
  @brief Converter uma Letra no seu indice
  */
#define IND(x) ((x) - 'A')

/**
\brief Faturas Lidas.
*/
struct faturas {
    int produtos;
    double totalFacts[12]; /**< Total faturado */
    int totalVendas[12];
    GTree* avlF[LETTERS][LETTERS]; /**< Matriz de AVL para guardar os faturas */
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

FatP searchFatura(const Faturas p, const char* id) {
    return g_tree_lookup(p->avlF[IND(id[0])][IND(id[1])], id);
}

double getFatTotal(const Faturas p, int mes) {
    return p->totalFacts[mes - 1];
}

int getQuantTotal(const Faturas p, int mes) {
    return p->totalVendas[mes - 1];
}

int getNVendasFaturas(const Faturas p, const char* id, int mes, Filial filial, Tipo tipo) {
    FatP f = g_tree_lookup(p->avlF[IND(id[0])][IND(id[1])], id);
    return f ? getNVendasFatura(f, mes, filial, tipo) : 0;
}

int getProdsVendidos (const Faturas f) {
    int i, j, r = 0;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            r += g_tree_nnodes(f->avlF[i][j]);
    return r;
}

static gboolean getAll(gpointer key, gpointer value, gpointer data) {
    FatP* array = *(FatP**) data;
    (void) key;
    *(array++) = cloneFat ((FatP) value);
    *(FatP**) data = array;
    return FALSE;
}

FatP* getAllList(const Faturas p, int* N) {
    int size, i, j;
    FatP* arrayr;
    FatP* array;
    size = getProdsVendidos(p);
    array = malloc(size * sizeof(FatP));
    arrayr = array;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_foreach(p->avlF[i][j], getAll, &arrayr);
    qsort(array, size, sizeof(FatP), cmpFat);
    for(i = *N; i < size; i++)
        destroyFact(array[i]);
    *N = *N > size ? size : *N;
    return array;
}

Faturas initFaturas() {
    int i, j;
    Faturas p = malloc(sizeof(struct faturas));
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            p->avlF[i][j] = g_tree_new_full(cmp, NULL, free, destroyFact);
    memset(p->totalFacts, 0, 12 * sizeof(double));
    memset(p->totalVendas, 0, 12 * sizeof(int));
    return p;
}

Faturas addFatura(const Venda p, Faturas l) {
    char* id = getProductSale(p);
    FatP ree = searchFatura(l, id);
    if(!ree) {
        ree = initFatP(p);
        g_tree_insert(l->avlF[IND(id[0])][IND(id[1])], id, ree);
    }
    else { 
        mkFatura(ree, p);
        free(id);
    }
    l->totalFacts[getMesSale(p) - 1] += getTotalSale(p);
    l->totalVendas[getMesSale(p) - 1]++;
    return l;
}

void clearFaturas(Faturas p) {
    int i, j;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_destroy(p->avlF[i][j]);
    free(p);
}
