FILES := *.o main
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lMLV -lm

all: clean main

main: main.c affichage.o Quadtree.o
	$(COMP) $(COMP_FLAGS) main.c affichage.o Quadtree.o -o main

affichage.o: affichage.c affichage.h
	$(COMP) $(COMP_FLAGS) -c affichage.c

Quadtree.o: Quadtree.c Quadtree.h
	$(COMP) $(COMP_FLAGS) -c Quadtree.c


clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done