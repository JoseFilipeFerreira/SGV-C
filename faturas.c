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
    GTree* naoComprados[4];
    double totalFacts[12]; /**< Total faturado */
    int totalVendas[12];
    GTree* avlF[LETTERS][LETTERS]; /**< Matriz de AVL para guardar os faturas */
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

static FatP searchFatura(const Faturas p, const char* id) {
    return g_tree_lookup(p->avlF[IND(id[0])][IND(id[1])], id);
}

double getFatTotal(const Faturas p, int mes) {
    return p->totalFacts[mes - 1];
}

int getQuantTotal(const Faturas p, int mes) {
    return p->totalVendas[mes - 1];
}

int getProdsVendidos (const Faturas f) {
    return f->produtos;
}

static gboolean naoComprados(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *(array++) = (char*) key;
    *(char***) data = array;
    return FALSE;
}

int getNaoComprados(const Faturas p, const Filial filial, char*** array) {
    int size;
    char** arrayr;
    size = g_tree_nnodes(p->naoComprados[filial]);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    g_tree_foreach(p->naoComprados[filial], naoComprados, &arrayr);
    return size;
}

Faturas initFaturas() {
    int i, j;
    Faturas p = malloc(sizeof(struct faturas));
    for(i = 0; i < 4; i++)
        p->naoComprados[i] = g_tree_new(cmp);
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            p->avlF[i][j] = g_tree_new_full(cmp, NULL, free, destroyFact);
    memset(p->totalFacts, 0, 12 * sizeof(double));
    memset(p->totalVendas, 0, 12 * sizeof(int));
    p->produtos = 0;
    return p;
}

void addNaoComprados(char* p, Faturas f) {
    int i;
    for(i = 0; i < 4; i++)
        g_tree_insert(f->naoComprados[i], p, p);
}

Faturas addFatura(const Venda p, Faturas l) {
    char* id = getProductSale(p);
    FatP ree = searchFatura(l, id);
    if(!ree) {
        l->produtos++;
        ree = initFatP(p);
        g_tree_insert(l->avlF[IND(id[0])][IND(id[1])], id, ree);
        g_tree_remove(l->naoComprados[ALL], id);
        g_tree_remove(l->naoComprados[getFilialSale(p)], id);
    }
    else { 
        mkFatura(ree, p);
        g_tree_remove(l->naoComprados[getFilialSale(p)], id);
        free(id);
    }
    l->totalFacts[getMesSale(p) - 1] += getTotalSale(p);
    l->totalVendas[getMesSale(p) - 1]++;
    return l;
}

void clearFaturas(Faturas p) {
    int i, j;
    for(i = 0; i < 4; i++) 
        g_tree_destroy(p->naoComprados[i]);
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_destroy(p->avlF[i][j]);
    free(p);
}
