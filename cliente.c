#include "cliente.h"

struct cliente {
    char* id;
};

int verifyClient(const char* id) {
    char c;
    int n;
    if(id && strlen(id) == 5) {
        sscanf(id, "%c%d%*s", &c, &n);
        return c <= 'Z' && c >='A'&& n >= 1000 && n <= 5000;
    }
    return 0;
}

Cliente mkClient(char* id) {
    char* client = malloc(strlen(id) + 1);
    Cliente cliente = malloc(sizeof(struct cliente));
    strcpy(client, strtok(id, "\n\r"));
    cliente->id = client;
    return cliente;
}

char* getIdClient(Cliente cliente) {
    char* r = malloc(strlen(cliente->id) + 1);
    strcpy(r, cliente->id);
    return r;
}

void destroyClient(void* cl) {
    Cliente cliente = (Cliente) cl;
    free(cliente->id);
    free(cliente);
}
