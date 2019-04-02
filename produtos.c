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
    GTree* avlP[LETTERS][LETTERS]; /**< Matriz de AVL para guardar os produtos */
};

typedef struct filialSearcher {
    int filial;
    char*** array;
} FilialSearcher;

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
    int i, j, r = 0;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            r += g_tree_nnodes(p->avlP[i][j]);
    return r;
}

static gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *array = malloc(strlen((char*) key) + 1);
    strcpy(*(array++), (char*) key);
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
    return p;
}

static gboolean naoComprados(gpointer key, gpointer value, gpointer struc) {
    FilialSearcher ree = *(FilialSearcher*) struc;
    char** array = *(ree.array);
    Produto r = (Produto) value;
    if(!foiCompradoOnde(ree.filial, r)) {
        *array = malloc(strlen((char*) key) + 1);
        strcpy(*(array++), (char*) key);
        *(ree.array) = array;
    }
    return FALSE;
}

int getNaoComprados(const Produtos p, const int filial, char*** array) {
    int size, i, j;
    char** arrayr;
    FilialSearcher ree;
    ree.filial = filial;
    size = getProductNumber(p);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    ree.array = &arrayr;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_foreach(p->avlP[i][j], naoComprados, &ree);
    return arrayr - *array;
}

Produtos addProduct(const Produto p, Produtos l) {
    char* id = getIdProduct(p);
    g_tree_insert(l->avlP[IND(id[0])][IND(id[1])], id, p);
    return l;
}

void produtosUpdateCompra(const char* id, char* cliente, int filial, Produtos r) {
    Produto p = g_tree_lookup(r->avlP[IND(id[0])][IND(id[1])], id);
    produtoAddQuemComprou(filial, cliente, p);
    updateCompra(p, filial);
}

int produtosQuantosCompraram(const char* id, int filial, Produtos r) {
    Produto p = g_tree_lookup(r->avlP[IND(id[0])][IND(id[1])], id);
    return produtoQuantosCompraram(filial, p);
}

int produtosQuemComprou(const char* id, char*** array, Produtos r) {
    Produto p = g_tree_lookup(r->avlP[IND(id[0])][IND(id[1])], id);
    return produtoQuemComprou(p, array);
}

void clearProducts(Produtos p) {
    int i, j;
    for(i = 0; i < LETTERS; i++)
        for(j = 0; j < LETTERS; j++)
            g_tree_destroy(p->avlP[i][j]);
    free(p);
}
