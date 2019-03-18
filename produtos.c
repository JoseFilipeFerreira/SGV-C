#include "produtos.h"

/**
  \brief AVL que contem os produtos.
  */
GTree* avlP[26];

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

Produto searchProduct(const char* id) {
    return g_tree_lookup(avlP[id[0] - 'A'], id);
}

void updateProduct(const char* id, int quantidade, int mes, int filial) {
    Produto produto = searchProduct(id);
    addQuantProduct(produto, filial, mes, quantidade);
}

int getProductNumber() {
    int res = 0, i;
    for(i = 0; i < 26; i++)
        res += g_tree_nnodes(avlP[i]);
    return res;
}

gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *(array++) = (char*) key;
    *(char***) data = array;
    return FALSE;
}

int getProductLetter(const char id, char*** array) {
    int size = g_tree_nnodes(avlP[id - 'A']);
    array = malloc(size * sizeof(char*));
    char*** arrayr = array;
    g_tree_foreach(avlP[id - 'A'], productLetter, arrayr);
    return size;
}

void initProducts(int filter, const char* path) {
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

void clearProducts() {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(avlP[i]);
}
