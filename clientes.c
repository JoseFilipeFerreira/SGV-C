#include "clientes.h"
#include <glib.h>

/**
\brief Array que contem os clientes.
*/
char* clientes[20000];

/**
\brief AVL que contem os clientes.
*/
GTree* avlC[26];

/**
\brief Número de clientes no array clientes.
*/
int clientNumber;

/**
\brief Lê os clientes de um ficheiro e coloca-os no array clientes.

@param path ficheiro onde estão os clientes
*/
void readClients(char * path) {
    int i;
    FILE* f = fopen(path, "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++) {
        clientes[i] = malloc(strlen(buff)+1);
        strcpy(clientes[i], strtok(buff, "\n\r"));
    }
    clientNumber = i;
    fclose(f);
}

int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

/**
\brief Filtra os clientes do array de clientes.
*/
void verifyClients() {
    int r, w, id;
    char c;
    FILE* f = fopen("db/ClientesOK.txt", "w");
    for(c = 'A'; c <= 'Z'; c++)
        avlC[c - 'A'] = g_tree_new_full(&cmp, NULL, &free, &free);
    for(r = w = 0; r < clientNumber; r++) {
        sscanf(clientes[r], "%c%4d%*s", &c, &id);
        if(verifyClient(clientes[r])) { 
            int* content = malloc(sizeof(int));
            fprintf(f, "%s\n", clientes[r]);
            *content = id;
            g_tree_insert(avlC[c - 'A'], clientes[r], content);
            if(w != r) {
                free(clientes[w]);
                clientes[w] = malloc(10);
                strcpy(clientes[w], clientes[r]);
            }
            w++;
        }
    }
    clientNumber = w;
    fclose(f);
}

int* searchClient(char* id) {
    return (int*) g_tree_lookup(avlC[id[0] - 'A'], id);
}

int getClientNumber() {
    return clientNumber;
}

gboolean clientLetter(gpointer key, gpointer value, gpointer data) {
    char* ree = (char*) key;
    int* r = ((int**) data)[0];
    char* id = (char*) ((int**) data)[1];
    (void) value;
    if(ree[0] > *id) return TRUE;
    if(ree[0] == *id) (*r)++;
    return FALSE;
}

int getClientLetter(char id) {
    return g_tree_nnodes(avlC[id - 'A']);
}

void initClients(int filter, char * path) {
    readClients(path);
    if(filter) verifyClients();
}

void clearClients() {
    int i;
    for(i = 0; i < 26; i++)
        g_tree_destroy(avlC[i]);
}
