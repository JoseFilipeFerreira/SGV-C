############################# Makefile ##########################
CFLAGS= -W -Wall -Wextra -pedantic -g -O2 -ansi `pkg-config --cflags --libs glib-2.0`

OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))
FICHEIROSVAL = db/ProdutosOK.txt db/ClientesOK.txt db/VendasOK.txt
BENCH = bench
IMAGE = $$(date +%F-%T)_memusage.png
DOC = docs
EXECUTAVEL=main.out

$(EXECUTAVEL): $(OBJECTS)
	cc $(CFLAGS) -o $(EXECUTAVEL) $(OBJECTS)

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

mem:
	memusage -T -p $(BENCH)/$(IMAGE) ./$(EXECUTAVEL)