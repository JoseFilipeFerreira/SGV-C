#include "cliente.h"

struct client {
    char* id;
    int quantF[3];
    double totalF[3];
};

int verifyClient(char* id) {
    char c1, c2;
    int n;
    sscanf(id, "%c%c%d%*s", &c1, &c2, &n);
    return strlen(id) == 6 && c1 <= 'Z' && c1 >='A' && c2 <= 'Z' && c2 >='A' && n >= 1000 && n <= 9999;
}

Client* mkClient(char* id) {
    Client* client = NULL;
    if(verifyClient(id)) {
        client = malloc(sizeof(struct client));
        client->id = malloc(strlen(id) + 1);
        strcpy(client->id, id);
        memset(client->quantF, 0, sizeof(client->quantF));
        memset(client->totalF, 0, sizeof(client->totalF));
    }
    return client;
}

void updateClient(Client* client, int quantity, double price, int filial) {
    client->quantF[filial-1] += quantity;
    client->totalF[filial-1] += price;
}
