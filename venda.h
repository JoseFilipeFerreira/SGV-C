#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "clientes.h"
#include <glib.h>

typedef struct venda* Venda;

int verifySale(const char*);

Venda mkSale(const char*);
