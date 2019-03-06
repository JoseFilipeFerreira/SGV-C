############################# Makefile ##########################
CFLAGS= -ansi -O2 

FICHEIROS= main.o produtos.o clientes.o vendas.o
FICHEIROSVAL = db/ProdutosOK.txt db/ClientesOK.txt db/VendasOK.txt
DOC = docs
EXECUTAVEL=main.out

$(EXECUTAVEL): $(FICHEIROS)
	gcc -o $(EXECUTAVEL) $(FICHEIROS)

run:
	./main.out

clean:
	rm -rf *.o $(EXECUTAVEL) $(FICHEIROSVAL) $(DOC)

inval:
	rm -rf $(FICHEIROSVAL)

doc:
	doxygen Doxygen

grind:
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all ./$(EXECUTAVEL)

vendas.o: clientes.h produtos.h
produtos.o: produtos.h
clientes.o: clientes.h
