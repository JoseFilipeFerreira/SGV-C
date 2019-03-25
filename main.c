/**
@file main.c
\brief Ficheiro principal.
*/
#include "controler.h"
#include "argv.h"

/**
  \brief Função principal.
  */
int main(int argc, char** argv) {
    if (argc == 1)
        menuInicial();
    else
      argvParser(argc, argv);
    return 0;
}
