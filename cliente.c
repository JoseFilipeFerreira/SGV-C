#include "cliente.h"

struct cliente {
    char* id;
};

int verifyClient(const char* id) {
    char c;
    int n;
    sscanf(id, "%c%d%*s", &c, &n);
    return strlen(id) == 5 && c <= 'Z' && c >='A'&& n >= 1000 && n <= 5000;
}

Cliente mkClient(char* id) {
    char* client = malloc(strlen(id) + 1);
    Cliente cliente = malloc(sizeof(struct cliente));
    strcpy(client, strtok(id, "\n\r"));
    cliente->id = client;
    return cliente;
}

const char* getIdClient(Cliente cliente) {
    return cliente->id;
}

void destroyClient(Cliente cliente) {
    free(cliente->id);
    free(cliente);
}
