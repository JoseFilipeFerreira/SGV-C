#include "produtos.h"
#include <glib.h>

/**
\brief Array que contem os produtos.
*/
char* produtos[200000];

/**
\brief AVL que contem os produtos.
*/
GTree* avlP[26];

/**
\brief Número de produtos no array produtos.
*/
int productNumber;

/**
\brief Lê os produtos de um ficheiro e coloca-os no array produtos.

@param path ficheiro onde estão os produtos
*/
void readProducts(char * path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++) {
        produtos[i] = malloc(10);
        strcpy(produtos[i], strtok(buff, "\n\r"));
    }
    free(buff);
    productNumber = i;
    fclose(f);
}

int cmp1(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

/**
\brief Filtra os produtos do array de produtos.
*/
void verifyProducts() {
    int r, w, id;
    char c;
    FILE* f = fopen("db/ProdutosOK.txt", "w");
    for(c = 'A'; c <= 'Z'; c++)
        avlP[c - 'A'] = g_tree_new_full(&cmp1, NULL, &free, &free);
    for(r = w = 0; r < productNumber; r++) {
        sscanf(produtos[r], "%c%*c%4d%*s", &c, &id);
        if(verifyProduct(produtos[r])) {
            int* content = malloc(sizeof(int));
            fprintf(f, "%s\n", produtos[r]);
            *content = id;
            g_tree_insert(avlP[c - 'A'], produtos[r], content);
            if(w != r) {
                free(produtos[w]);
                produtos[w] = malloc(10); 
                strcpy(produtos[w], produtos[r]); 
            }
            w++;
        }
    }
    productNumber = w;
    fclose(f);
}

int* searchProduct(char* id) {
    return (int*) g_tree_lookup(avlP[id[0] - 'A'], id);
}

int getProductNumber() {
    return productNumber;
}

gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char* ree = (char*) key;
    int* r = ((int**) data)[0];
    char* id = (char*) ((int**) data)[1];
    (void) value;
    if(ree[0] > *id) return TRUE;
    if(ree[0] == *id) (*r)++;
    return FALSE;
}

int getProductLetter(char id) {
    return g_tree_nnodes(avlP[id - 'A']);
}

void initProducts(int filter, char * path) {
    readProducts(path);
    if(filter) verifyProducts();
}

void clearProducts() {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(avlP[i]);
}
