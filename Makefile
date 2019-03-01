############################# Makefile ##########################
CFLAGS= -ansi -O2 

FICHEIROS= main.o produtos.o clientes.o vendas.o
EXECUTAVEL=main.out

$(EXECUTAVEL): $(FICHEIROS)
	gcc -o $(EXECUTAVEL) $(FICHEIROS)

clean:
	rm -rf *.o $(EXECUTAVEL) db/*Validas.txt db/*Validos.txt

inval:
	rm -rf *.o db/*Validas.txt db/*Validos.txt

grind:
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all ./$(EXECUTAVEL)

vendas.o: clientes.h produtos.h
produtos.o: produtos.h
clientes.o: clientes.h
