#include "produtos.h"
#include "clientes.h"

int main() {
    int clientNumber = verifyClients(readClients());
    int productNumber = verifyProducts(readProducts());
    printf("%d\n", searchClient("F2916\r\n",clientNumber));
}
