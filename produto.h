#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto* Produto;

int verifyProduct(const char*);

Produto mkProduct(char*);

void addFactProduct(Produto, int, int, int, char);

void addQuantProduct(Produto, int, int, int);

const char* getIdProduct(Produto);

void destroyProduct(Produto);

void printProduct(Produto);
