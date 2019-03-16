#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct client Client;

int verifyClient(char*);

Client* mkClient(char*);

void updateClient(Client*, int, double, int);
