#include "Quadtree.h"

int main(int argc, char** argv) {
    Quadtree qd = initQuadtree(100, 10);
    Particle* p = generateParticles(100);
    freeQuadtree(qd);
    free(p);
    return 0;
}
