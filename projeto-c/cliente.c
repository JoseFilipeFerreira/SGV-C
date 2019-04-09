#include "cliente.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct cliente {
    char* id; /**< ID do Cliente*/
    bool comprou[3]; /**< Informação em que filial comprou */
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

void updateBuyClient(Cliente c, int filial) {
    c->comprou[filial] = true;
}

bool comprouOnde(int filial, Cliente p) {
    return p->comprou[filial];
}

Cliente mkClient(char* id) {
    char* client = malloc(strlen(id) + 1);
    Cliente cliente = malloc(sizeof(struct cliente));
    strcpy(client, strtok(id, "\n\r"));
    cliente->id = client;
    memset(cliente->comprou, false, 3 * sizeof(bool));
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

