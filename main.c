#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

int main() {
    initDB(1);
    printf("%d %d %d\n", getSalesNumber(), getClientNumber(), getProductNumber());
    return 0;
}
