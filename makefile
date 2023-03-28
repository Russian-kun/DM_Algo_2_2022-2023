FILES := *.o main
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lncurses

main: MyMalloc.o
	$(COMP) $(COMP_FLAGS) -o main MyMalloc.o main.c

MyMalloc.o: MyMalloc.c MyMalloc.h
	$(COMP) $(COMP_FLAGS) -c MyMalloc.c

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done