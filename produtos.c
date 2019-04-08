#include "produtos.h"
#include <gmodule.h>

struct produtos {
    GHashTable* avlP; /**< Hashtable para guardar os produtos */
};

typedef struct filialSearcher {
    int filial; /**< Filial referente à lista de produtos*/
    char*** array; /**< Lista com os produtos vendidos numa filial*/
} FilialSearcher;

bool searchProduct(const Produtos p, const char* id) {
    if(verifyProduct(id)) 
        return (g_hash_table_lookup(p->avlP, id) != NULL);
    return false;
}

int getProductNumber(const Produtos p) {
    return g_hash_table_size(p->avlP);
}

static int sortL(const void* a, const void* b) {
    return strcmp(*(char**) a, *(char**) b);
}

static void productLetter(gpointer key, gpointer value, gpointer data) {
    FilialSearcher ree = *(FilialSearcher*) data;
    char** array = *(ree.array);
    (void) value;
    if(((char*) key)[0] == ree.filial) {
        *array = malloc(strlen((char*) key) + 1);
        strcpy(*(array++), (char*) key);
        *(ree.array) = array;
    }
}

int getProductLetter(const Produtos p, const char id, char*** array) {
    int size;
    char** arrayr;
    FilialSearcher r;
    r.filial = id;
    size = g_hash_table_size(p->avlP);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    r.array = &arrayr;
    g_hash_table_foreach(p->avlP, productLetter, &r);
    qsort(*array, arrayr - *array, sizeof(char*), sortL);
    return arrayr- *array;
}

Produtos initProducts() {
    Produtos p = malloc(sizeof(struct produtos));
    p->avlP= g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyProduct);
    return p;
}

static void naoComprados(gpointer key, gpointer value, gpointer struc) {
    FilialSearcher ree = *(FilialSearcher*) struc;
    char** array = *(ree.array);
    Produto r = (Produto) value;
    if(!foiCompradoOnde(ree.filial, r)) {
        *array = malloc(strlen((char*) key) + 1);
        strcpy(*(array++), (char*) key);
        *(ree.array) = array;
    }
}

int getNaoComprados(const Produtos p, const int filial, char*** array) {
    int size;
    char** arrayr;
    FilialSearcher ree;
    ree.filial = filial;
    size = getProductNumber(p);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    ree.array = &arrayr;
    g_hash_table_foreach(p->avlP, naoComprados, &ree);
    qsort(*array, arrayr- *array , sizeof(char*), sortL);
    return arrayr - *array;
}

Produtos addProduct(const Produto p, Produtos l) {
    char* id = getIdProduct(p);
    g_hash_table_insert(l->avlP, id, p);
    return l;
}

void produtosUpdateCompra(const char* id, int filial, Produtos r) {
    Produto p = g_hash_table_lookup(r->avlP, id);
    if(p)
        updateCompra(p, filial);
}

void clearProducts(Produtos p) {
    g_hash_table_destroy(p->avlP);
    free(p);
}
