#include "clientes.h"
#include <glib.h>

/**
  \brief AVL que contem os clientes.
  */
GTree* avlC[26];

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

void* searchClient(const char* id) {
    return g_tree_lookup(avlC[id[0] - 'A'], id);
}

int getClientNumber() {
    int res = 0, i;
    for(i = 0; i < 26; i++)
        res += g_tree_nnodes(avlC[i]);
    return res;
}

static gboolean clientLetter(gpointer key, gpointer value, gpointer data) {
    char* ree = (char*) key;
    int* r = ((int**) data)[0];
    char* id = (char*) ((int**) data)[1];
    (void) value;
    if(ree[0] > *id) return TRUE;
    if(ree[0] == *id) (*r)++;
    return FALSE;
}

int getClientLetter(const char id) {
    return g_tree_nnodes(avlC[id - 'A']);
}

void initClients(int filter, const char* path) {
    int i;
    FILE* f = fopen(path, "r");
    FILE* ff = fopen("db/ClientesOK.txt", "w");
    char* buff = malloc(10);
    for(i = 'A'; i <= 'Z'; i++)
        avlC[i - 'A'] = g_tree_new_full(&cmp, NULL, &free, NULL);
    for(i = 0; fgets(buff, 10, f);) {
        if(!filter || verifyClient(strtok(buff, "\n\r"))) {
            char* client = mkClient(buff);
            g_tree_insert(avlC[client[0] - 'A'], client, client);
            i++;
            fprintf(ff, "%s\n", client);
        }
    }
    fclose(ff);
    free(buff);
    fclose(f);
}

void clearClients() {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(avlC[i]);
}
