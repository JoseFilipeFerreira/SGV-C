#include "clientes.h"
#include <glib.h>

/**
\brief Array que contem os clientes.
*/
char* clientes[20000];

/**
\brief AVL que contem os clientes.
*/
GTree* avlC;

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

int cmp(const void* a, const void* b) {
    return strcmp((char*) a, (char*) b);
}

/**
\brief Filtra os clientes do array de clientes.
*/
void verifyClients() {
    int r, w, id;
    char c;
    avlC = g_tree_new(&cmp);
    FILE* f = fopen("db/ClientesOK.txt", "w");
    for(r = w = 0; r < clientNumber; r++) {
        sscanf(clientes[r], "%c%4d%*s", &c, &id);
        if(id >= 1000 && id <= 5000 && c <= 'Z' && c >= 'A') { 
            fprintf(f, "%s\n", clientes[r]);
            int* content = malloc(sizeof(int));
            *content = id;
            g_tree_insert(avlC, clientes[r], content);
            if(w != r) {
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
    return (int*) g_tree_lookup(avlC, id);
}

int getClientNumber() {
    return clientNumber;
}

int getClientLetter(char id) {
    int i, r;
    r = 0;
    for(i = 0; i < clientNumber; i++)
        if(clientes[i][0] == id) r++;
    return r;
}

void initClients(int filter, char * path) {
    readClients(path);
    if(filter) verifyClients();
}
