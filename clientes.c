#include "clientes.h"

#define LETTERS 26
#define IND(x) ((x) - 'A')

/**
  \brief AVL que contem os clientes.
  */
struct clientes {
    int totalProds;
    GTree* avlC[LETTERS];
};

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

int searchClient(const Clientes p, const char* id) {
    if(verifyClient(id))
        return g_tree_lookup(p->avlC[IND(id[0])], id);
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
    *array = malloc(size * sizeof(char*));
    char** arrayr = *array;
    g_tree_foreach(p->avlC[IND(id)], clientLetter, &arrayr);
    return size;
}

Clientes initClients() {
    int i;
    Clientes p = malloc(sizeof(struct clientes));
    for(i = 0; i < LETTERS; i++)
        p->avlC[i] = g_tree_new_full(&cmp, NULL, NULL, destroyClient);
    p->totalProds = 0;
    return p;
}

Clientes addClient(Cliente p, Clientes l) {
    const char* id = getIdClient(p);
    l->totalProds++;
    g_tree_insert(l->avlC[id[0] - 'A'], id, p);
    return l;
}
/*
static void init(int filter, const char* path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(10);
    FILE* ff = fopen("db/ClientesOK.txt", "w");
    for(i = 'A'; i <= 'Z'; i++)
        avlC[i - 'A'] = g_tree_new_full(&cmp, NULL, NULL, destroyClient);
    for(i = 0; fgets(buff, 10, f);) {
        if(!filter || verifyClient(strtok(buff, "\n\r"))) {
            Cliente client = mkClient(buff);
            g_tree_insert(avlC[getIdClient(client)[0] - 'A'], getIdClient(client), client);
            i++;
            fprintf(ff, "%s\n", getIdClient(client));
        }
    }
    fclose(ff);
    free(buff);
    fclose(f);
}
*/
void clearClients(Clientes p) {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(p->avlC[i]);
    free(p);
}
