FILES := *.o main
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lMLV -lm
OBJ := affichage.o Quadtree.o Cell.o

all: clean main

main: main.c $(OBJ)
	$(COMP) $(COMP_FLAGS) main.c $(OBJ) -o main

affichage.o: affichage.c affichage.h Cell.o Quadtree.o
	$(COMP) $(COMP_FLAGS) -c affichage.c

Quadtree.o: Quadtree.c Quadtree.h Cell.o
	$(COMP) $(COMP_FLAGS) -c Quadtree.c

Cell.o: Cell.c Cell.h
	$(COMP) $(COMP_FLAGS) -c Cell.c


clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done