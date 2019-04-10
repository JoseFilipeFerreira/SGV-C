############################# Makefile ##########################
CFLAGS= -W -Wall -Wextra -ansi -O2 -D_GNU_SOURCE `pkg-config --cflags --libs glib-2.0`

OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))
BENCH = ../bench
IMAGE = $$(date +%F-%T)_memusage.png
DOC = ../docs
EXECUTAVEL=SGV

$(EXECUTAVEL): $(OBJECTS)
	cc -o $(EXECUTAVEL) $(OBJECTS) $(CFLAGS)

run:
	./$(EXECUTAVEL)

clean:
	rm -rf *.o $(EXECUTAVEL) $(DOC)

doc:
	doxygen Doxygen
	mv docs ..

grind:
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all ./$(EXECUTAVEL) 1

mem:
	memusage -T -p $(BENCH)/$(IMAGE) ./$(EXECUTAVEL) 13
