#include "clientes.h"

#define LETTERS 26
#define IND(x) ((x) - 'A')

/**
\brief AVL que contem os clientes.
*/
struct clientes {
    int totalProds; /**< Número de clientes lidos */
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
    return p->totalProds;
}

static gboolean clientLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *(array++) = (char*) key;
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

Clientes initClients() {
    int i;
    Clientes p = malloc(sizeof(struct clientes));
    for(i = 0; i < LETTERS; i++)
        p->avlC[i] = g_tree_new_full(&cmp, NULL, free, destroyClient);
    p->totalProds = 0;
    return p;
}

Clientes addClient(const Cliente p, Clientes l) {
    char* id = getIdClient(p);
    l->totalProds++;
    g_tree_insert(l->avlC[id[0] - 'A'], (void*) id, p);
    return l;
}

void clearClients(Clientes p) {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(p->avlC[i]);
    free(p);
}
