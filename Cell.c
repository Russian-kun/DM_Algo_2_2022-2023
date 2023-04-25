#include "Cell.h"

#include <stdlib.h>

Cell* getLastCell(Cell* cell) {
    if (cell == NULL)
        return NULL;
    while (cell->next != NULL) {
        cell = cell->next;
    }
    return cell;
}

Particle* generateParticles(int nbp, Cell** cell, int W) {
    Particle* particules = (Particle*)malloc(nbp * sizeof(Particle));
    *cell = calloc(nbp, sizeof(Cell));
    for (int i = 0; i < nbp; i++) {
        int x = rand() % W;
        int y = rand() % W;
        particules[i] = (Particle){x, y, 0, 0};
        (*cell)[i] = (Cell){&particules[i], NULL};
    }
    return particules;
}
