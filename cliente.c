#include "cliente.h"

int verifyClient(char* id) {
    char c;
    int n;
    sscanf(id, "%c%d%*s", &c, &n);
    return strlen(id) == 5 && c <= 'Z' && c >='A' && n >= 1000 && n <= 9999;
}

char* mkClient(char* id) {
    char* client = malloc(strlen(id) + 1);
    strcpy(client, strtok(id, "\n\r"));
    return client;
}
