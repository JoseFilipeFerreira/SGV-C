#include "produtos.h"

#define LETTERS 26
#define IND(x) ((x) - 'A')

/**
  \brief AVL que contem os produtos.
  */
struct produtos {
    int totalProds;
    GTree* avlP[LETTERS];
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

int searchProduct(const Produtos p, const char* id) {
    return g_tree_lookup(p->avlP[IND(id[0])], id);
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
    int size = g_tree_nnodes(p->avlP[IND(id)]);
    *array = malloc(size * sizeof(char*));
    char** arrayr = *array;
    g_tree_foreach(p->avlP[IND(id)], productLetter, &arrayr);
    return size;
}

Produtos initProducts() {
    int i;
    Produtos p = malloc(sizeof(struct produtos));
    for(i = 0; i < LETTERS; i++)
        p->avlP[i] = g_tree_new_full(&cmp, NULL, NULL, destroyProduct);
    p->totalProds = 0;
    return p;
}

Produtos addProduct(Produto p, Produtos l) {
    const char* id = getIdProduct(p);
    l->totalProds++;
    g_tree_insert(l->avlP[id[0] - 'A'], id, p);
    return l;
}
/*
static void init(int filter, const char* path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(10);
    FILE* ff = fopen("db/ProdutosOK.txt", "w");
    for(i = 'A'; i <= 'Z'; i++)
        avlP[i - 'A'] = g_tree_new_full(&cmp, NULL, NULL, destroyProduct);
    for(i = 0; fgets(buff, 10, f);) {
        if(!filter || verifyProduct(strtok(buff, "\n\r"))) {
            Produto product = mkProduct(buff);
            g_tree_insert(avlP[getIdProduct(product)[0] - 'A'], getIdProduct(product), product);
            i++;
            fprintf(ff, "%s\n", getIdProduct(product));
        }
    }
    fclose(ff);
    free(buff);
    fclose(f);
}
*/
void clearProducts(Produtos p) {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(p->avlP[i]);
    free(p);
}
