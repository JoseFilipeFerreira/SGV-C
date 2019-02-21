#include "produtos.h"
#include "clientes.h"

int main() {
    initClients();
    printf("%d\n", searchClient("F2916"));
    printf("%d\n", getClientLetter('B'));
}
