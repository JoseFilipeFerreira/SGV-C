#include "clientes.h"

char* clientes[20000];

int readClients() {
    int i;
    FILE* f = fopen("./db/Clientes.txt", "r");
    char* buff = malloc(10);
    for(i = 0; fgets(buff, 10, f); i++)
        clientes[i] = strdup(buff);
    return i;
}

int verifyClients(int n) {
    int r, w, id;
    for(r = w = 0; r < n; r++) {
        sscanf(clientes[r], "%*c%4d%*s", &id);
        if(id >= 1000 && id <= 5000) 
            clientes[w++] = strdup(clientes[r]);
    }
    return w;
}

int searchClient(char* id, int n) {
    int i;
    for(i = 0; i < n; i++)
        if(!strcmp(clientes[i], id)) return 1;
    return 0;
}
