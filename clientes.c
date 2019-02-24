#include "clientes.h"
#include <gmodule.h>

char* clientes[20000];
GHashTable* clientTable;
int clientNumber;

void readClients() {
    int i;
    FILE* f = fopen("./db/Clientes.txt", "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++) {
        clientes[i] = malloc(10);
        strcpy(clientes[i], buff);
        clientes[i][5] = '\0';
    }
    clientNumber = i;
    fclose(f);
}

void verifyClients() {
    int r, w, id;
    clientTable = g_hash_table_new(g_str_hash, g_str_equal);
    for(r = w = 0; r < clientNumber; r++) {
        sscanf(clientes[r], "%*c%4d%*s", &id);
        if(id >= 1000 && id <= 5000) { 
            if(g_hash_table_add(clientTable, clientes[r]))
                w++;
        }
    }
    clientNumber = w;
}

int searchClient(char* id) {
    return (g_hash_table_contains(clientTable, id) != 0L);
}

int getClientNumber() {
    return clientNumber;
}

int getClientLetter(char id) {
    int r;
    r = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, clientTable);
    while(g_hash_table_iter_next(&iter, &key, &value))
            if(((char*)key)[0] == id) r++;
    return r;
}

void initClients() {
    readClients();
    verifyClients();
}
