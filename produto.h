#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct product Product;

int verifyProduct(char*);

Product* mkProduct(char*);

void updateProduct(Product*, int, double, int);
