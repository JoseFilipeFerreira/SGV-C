#include "produtos.h"
#include "clientes.h"
#include "vendas.h"

int main() {
    initDB(); 
    printf("%d %d %d\n", getSalesNumber(), getClientNumber(), getProductNumber());
}
