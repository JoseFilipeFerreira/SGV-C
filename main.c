#include "produtos.h"
#include "clientes.h"

int main() {
    initClients();
    int productNumber = verifyProducts(readProducts());
    printf("%d\n", searchClient("F2916\r\n"));
}
