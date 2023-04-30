FILES := *.o main
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lMLV -lm
OBJ := affichage.o Quadtree.o Cell.o param.o

all: clean main

main: main.o $(OBJ)
	$(COMP) $(COMP_FLAGS) -o main main.o $(OBJ)

main.o: main.c affichage.h Quadtree.h Cell.h
	$(COMP) $(COMP_FLAGS) -c main.c

affichage.o: affichage.c affichage.h Cell.o Quadtree.o
	$(COMP) $(COMP_FLAGS) -c affichage.c

Quadtree.o: Quadtree.c Quadtree.h Cell.o
	$(COMP) $(COMP_FLAGS) -c Quadtree.c

Cell.o: Cell.c Cell.h
	$(COMP) $(COMP_FLAGS) -c Cell.c

param.o: param.c param.h
	$(COMP) $(COMP_FLAGS) -c param.c

docs: Doxyfile *.c *.h
	doxygen Doxyfile

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done
	if [ -d docs ]; then \
		rm -r docs; \
	fi