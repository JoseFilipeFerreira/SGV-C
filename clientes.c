#include "clientes.h"
#include <string.h>
#include <stdlib.h>

#define LETTERS 26
#define IND(x) ((x) - 'A')

/**
\brief AVL que contem os clientes.
*/
struct clientes {
    GTree* avlC[LETTERS]; /**< Array de AVL para guardar os clientes lidos */
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

int searchClient(const Clientes p, const char* id) {
    if(verifyClient(id))
        return g_tree_lookup(p->avlC[IND(id[0])], id) != NULL;
    return 0;
}

int getClientNumber(const Clientes p) {
    int i, r = 0;
    for(i = 0; i < LETTERS; i++)
        r += g_tree_nnodes(p->avlC[i]);
    return r;
}

static gboolean clientLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *array = malloc(strlen((char*) key) + 1);
    strcpy(*(array++), (char*) key);
    *(char***) data = array;
    return FALSE;
}


int getClientLetter(const Clientes p, const char id, char*** array) {
    int size = g_tree_nnodes(p->avlC[IND(id)]);
    char** arrayr;
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    g_tree_foreach(p->avlC[IND(id)], clientLetter, &arrayr);
    return size;
}

static gboolean comprou(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    Cliente r = (Cliente) value;
    if(comprouOnde(0, r) && comprouOnde(1, r) && comprouOnde(2, r)) {
        *array = malloc(strlen((char*) key) + 1);
        strcpy(*(array++), (char*) key);
        *(char***) data = array;
    }
    return FALSE;
}

int getComprador(const Clientes p, char*** array) {
    int size, i;
    char** arrayr;
    size = getClientNumber(p);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    for(i = 0; i < LETTERS; i++)
         g_tree_foreach(p->avlC[i], comprou, &arrayr);
    return arrayr - *array;
}

static gboolean naoComprou(gpointer key, gpointer value, gpointer data) {
    (void) key;
    Cliente r = (Cliente) value;
    if(!comprouOnde(0, r) && !comprouOnde(1, r) && !comprouOnde(2, r))
        (*(int*) data)++;
    return FALSE;
}

int getClientesNaoCompradores(const Clientes p) {
    int i, r = 0;
    for(i = 0; i < LETTERS; i++)
         g_tree_foreach(p->avlC[i], naoComprou, &r);
    return r;
}

Clientes initClients() {
    int i;
    Clientes p = malloc(sizeof(struct clientes));
    for(i = 0; i < LETTERS; i++)
        p->avlC[i] = g_tree_new_full(&cmp, NULL, free, destroyClient);
    return p;
}

void clientesUpdateCompra(const char* id, int filial, int mes, int quant, Clientes r) {
    Cliente p = g_tree_lookup(r->avlC[IND(id[0])], id);
    updateBuyClient(p, filial, mes, quant);
}


Clientes addClient(const Cliente p, Clientes l) {
    char* id = getIdClient(p);
    g_tree_insert(l->avlC[id[0] - 'A'], (void*) id, p);
    return l;
}

int getClientQuant(const char* id, int mes, int filial, const Clientes c) {
    Cliente p = g_tree_lookup(c->avlC[IND(id[0])], id);
    return getClientQuantidades(p, mes, filial);
}

void clearClients(Clientes p) {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(p->avlC[i]);
    free(p);
}
