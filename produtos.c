#include "produtos.h"
#include <glib.h>

/**
\brief Array que contem os produtos.
*/
char* produtos[200000];

/**
\brief AVL que contem os produtos.
*/
GTree* avlP;

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
    return strcmp((char*) a, (char*) b);
}

/**
\brief Filtra os produtos do array de produtos.
*/
void verifyProducts() {
    int r, w, id;
    avlP = g_tree_new_full(&cmp1, NULL, &free, &free);
    FILE* f = fopen("db/ProdutosOK.txt", "w");
    for(r = w = 0; r < productNumber; r++) {
        sscanf(produtos[r], "%*2c%4d%*s", &id);
        if(id >= 1000 && id <= 9999) {
            fprintf(f, "%s\n", produtos[r]);
            int* content = malloc(sizeof(int));
            *content = id;
            g_tree_insert(avlP, produtos[r], content);
            if(w != r) {
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
    return (int*) g_tree_lookup(avlP, id);
}

int getProductNumber() {
    return productNumber;
}

gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char* ree = (char*) key;
    int* r = (int*) ((int**) data)[0];
    char* id = (char*) ((int**) data)[1];
    if(ree[0] > *id) return TRUE;
    if(ree[0] == *id) (*r)++;
    return FALSE;
}

int getProductLetter(char id) {
    int r;
    r = 0;
    void* cenas[2] = {&r, &id};
    g_tree_foreach(avlP, productLetter, &cenas);
    return r;
}

void initProducts(int filter, char * path) {
    readProducts(path);
    if(filter) verifyProducts();
}
