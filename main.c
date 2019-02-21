#include "produtos.h"
#include "clientes.h"

int main() {
    initClients();
    initProducts();
    printf("Client Cenas exists? %d\n", searchClient("F2916"));
    printf("Product Cenas exists? %d\n", searchProduct("FD1087"));
    printf("%d\n", getClientLetter('B'));
}
