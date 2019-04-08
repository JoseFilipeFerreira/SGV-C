#include "clientes.h"
#include <string.h>
#include <stdlib.h>
#include "glibW.h"

struct clientes {
    GHashTable* avlC; /**< Hashtable para guardar os clientes lidos */
};

int searchClient(const Clientes p, const char* id) {
    if(verifyClient(id))
        return g_hash_table_lookup(p->avlC, id) != NULL;
    return 0;
}

int getClientNumber(const Clientes p) {
    return g_hash_table_size(p->avlC);
}


static int sortL(const void* a, const void* b) {
    return strcmp(*(char**) a, *(char**) b);
}

static void comprou(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    Cliente r = (Cliente) value;
    if(comprouOnde(0, r) && comprouOnde(1, r) && comprouOnde(2, r)) {
        *array = malloc(strlen((char*) key) + 1);
        strcpy(*(array++), (char*) key);
        *(char***) data = array;
    }
}

int getComprador(const Clientes p, char*** array) {
    int size;
    char** arrayr;
    size = getClientNumber(p);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    g_hash_table_foreach(p->avlC, comprou, &arrayr);
    qsort(*array, arrayr- *array, sizeof(char*), sortL);
    return arrayr - *array;
}

static void naoComprou(gpointer key, gpointer value, gpointer data) {
    (void) key;
    Cliente r = (Cliente) value;
    if(!comprouOnde(0, r) && !comprouOnde(1, r) && !comprouOnde(2, r))
        (*(int*) data)++;
}

int getClientesNaoCompradores(const Clientes p) {
    int r = 0;
    g_hash_table_foreach(p->avlC, naoComprou, &r);
    return r;
}

Clientes initClients() {
    Clientes p = malloc(sizeof(struct clientes));
    p->avlC = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyClient);
    return p;
}

void clientesUpdateCompra(const char* id, int filial, Clientes r) {
    Cliente p = g_hash_table_lookup(r->avlC, id);
    if(p)
        updateBuyClient(p, filial);
}


Clientes addClient(const Cliente p, Clientes l) {
    char* id = getIdClient(p);
    g_hash_table_insert(l->avlC, (void*) id, p);
    return l;
}

void clearClients(Clientes p) {
    g_hash_table_destroy(p->avlC);
    free(p);
}
