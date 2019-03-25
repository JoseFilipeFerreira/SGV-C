#include "cliente.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
@brief Struct para representar a informação de um cliente
*/
struct cliente {
    char* id; /**< ID do Cliente*/
};

bool verifyClient(const char* id) {
    char c;
    int n;
    if(id && strlen(id) == 5) {
        sscanf(id, "%c%d%*s", &c, &n);
        return c <= 'Z' && c >='A'&& n >= 1000 && n <= 5000;
    }
    return false;
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

