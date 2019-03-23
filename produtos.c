#include "produtos.h"

/**
@brief Número de Letras no alfabeto
*/
#define LETTERS 26

/**
@brief Converter uma Letra no seu indice
*/
#define IND(x) ((x) - 'A')

/**
\brief Produtos Lidos.
*/
struct produtos {
    int totalProds; /**< Número de produtos lidos */
    GTree* avlP[LETTERS][LETTERS]; /**< Matriz de AVL para guardar os produtos */
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

bool searchProduct(const Produtos p, const char* id) {
    if(verifyProduct(id)) 
        return (g_tree_lookup(p->avlP[IND(id[0])][IND(id[1])], id) != NULL);
    return false;
}

int getProductNumber(const Produtos p) {
    return p->totalProds;
}

static gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *(array++) = (char*) key;
    *(char***) data = array;
    return FALSE;
}

int getProductLetter(const Produtos p, const char id, char*** array) {
    int i, size = 0;
    char** arrayr;
    for(i = 0; i < LETTERS; i++) 
        size += g_tree_nnodes(p->avlP[IND(id)][i]);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    for(i = 0; i < LETTERS; i++)
        g_tree_foreach(p->avlP[IND(id)][i], productLetter, &arrayr);
    return size;
}

Produtos initProducts() {
    int i, j;
    Produtos p = malloc(sizeof(struct produtos));
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            p->avlP[i][j] = g_tree_new_full(&cmp, NULL, free, destroyProduct);
    p->totalProds = 0;
    return p;
}

Produtos addProduct(const Produto p, Produtos l) {
    char* id = getIdProduct(p);
    l->totalProds++;
    g_tree_insert(l->avlP[IND(id[0])][IND(id[1])], id, p);
    return l;
}

void clearProducts(Produtos p) {
    int i, j;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_destroy(p->avlP[i][j]);
    free(p);
}
