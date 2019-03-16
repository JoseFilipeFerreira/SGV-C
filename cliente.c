#include "cliente.h"

int verifyClient(char* id) {
    char c;
    int n;
    sscanf(id, "%c%d%*s", &c, &n);
    return strlen(id) == 5 && c <= 'Z' && c >='A' && n >= 1000 && n <= 9999;
}
