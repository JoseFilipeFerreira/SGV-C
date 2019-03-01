############################# Makefile ##########################
CFLAGS= -ansi -O2 

FICHEIROS= main.o produtos.o clientes.o vendas.o
FICHEIROSVAL = db/ProdutosOK.txt db/ClientesOK.txt db/VendasOK.txt
EXECUTAVEL=main.out

$(EXECUTAVEL): $(FICHEIROS)
	gcc -o $(EXECUTAVEL) $(FICHEIROS)

clean:
	rm -rf *.o $(EXECUTAVEL) $(FICHEIROSVAL)

inval:
	rm -rf $(FICHEIROSVAL)

grind:
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all ./$(EXECUTAVEL)

vendas.o: clientes.h produtos.h
produtos.o: produtos.h
clientes.o: clientes.h
