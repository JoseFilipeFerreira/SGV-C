#include "faturas.h"
#include <gmodule.h>

struct faturas {
    double totalFacts[12]; /**< Total faturado */
    int totalVendas[12];  /**< Total de vendas*/
    GHashTable* avlF; /**< Hashtable para guardar os faturas */
};

FatP searchFatura(const Faturas p, const char* id) {
    return g_hash_table_lookup(p->avlF, id);
}

double getFatTotal(const Faturas p, int mes) {
    return p->totalFacts[mes - 1];
}

int getQuantTotal(const Faturas p, int mes) {
    return p->totalVendas[mes - 1];
}

int getNVendasFaturas(const Faturas p, const char* id, int mes, Filial filial, Tipo tipo) {
    FatP f = g_hash_table_lookup(p->avlF, id);
    return f ? getNVendasFatura(f, mes, filial, tipo) : 0;
}

int getProdsVendidos (const Faturas f) {
    return g_hash_table_size(f->avlF);
}

static void getAll(gpointer key, gpointer value, gpointer data) {
    FatP* array = *(FatP**) data;
    (void) key;
    *(array++) = cloneFat ((FatP) value);
    *(FatP**) data = array;
}

FatP* getAllList(const Faturas p, int* N) {
    int size, i;
    FatP* arrayr;
    FatP* array;
    size = getProdsVendidos(p);
    array = malloc(size * sizeof(FatP));
    arrayr = array;
    g_hash_table_foreach(p->avlF, getAll, &arrayr);
    qsort(array, size, sizeof(FatP), cmpFat);
    for(i = *N; i < size; i++)
        destroyFact(array[i]);
    *N = *N > size ? size : *N;
    return array;
}

Faturas initFaturas() {
    Faturas p = malloc(sizeof(struct faturas));
    p->avlF = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyFact);
    memset(p->totalFacts, 0, 12 * sizeof(double));
    memset(p->totalVendas, 0, 12 * sizeof(int));
    return p;
}

void addFatura(const Venda p, Faturas l) {
    char* id = getProductSale(p);
    FatP ree = searchFatura(l, id);
    if(!ree) {
        ree = initFatP(p);
        g_hash_table_insert(l->avlF, id, ree);
    }
    else { 
        mkFatura(ree, p);
        free(id);
    }
    l->totalFacts[getMesSale(p) - 1] += getTotalSale(p);
    l->totalVendas[getMesSale(p) - 1]++;
}

void clearFaturas(Faturas p) {
    g_hash_table_destroy(p->avlF);
    free(p);
}
