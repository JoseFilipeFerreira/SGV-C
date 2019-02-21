#include "clientes.h"

char* clientes[20000];
int clientNumber;

void readClients() {
    int i;
    FILE* f = fopen("./db/Clientes.txt", "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++)
        clientes[i] = strdup(buff);
    clientNumber = i;
}

void verifyClients() {
    int r, w, id;
    for(r = w = 0; r < clientNumber; r++) {
        sscanf(clientes[r], "%*c%4d%*s", &id);
        if(id >= 1000 && id <= 5000) 
            clientes[w++] = strdup(clientes[r]);
    }
    clientNumber = w;
}

int searchClient(char* id) {
    int i;
    for(i = 0; i < clientNumber; i++)
        if(!strcmp(clientes[i], id)) return 1;
    return 0;
}

void initClients() {
    readClients();
    verifyClients();
}
