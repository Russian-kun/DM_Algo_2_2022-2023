#include "Quadtree.h"
#include "affichage.h"
#include <time.h>

int main(int argc, char* argv[]) {
    int W = 512, wmin = 10, kp = 100;
    int nbp = 500;
    Cell* lstCell = NULL;
    srand(time(NULL));
    Quadtree qd = initQuadtree(W, wmin);
    Particle* p = generateParticles(nbp, &lstCell);
    addParticlesQuadtree(qd, p, lstCell, nbp, kp);

    MLV_create_window("Quadtree", "Quadtree", W, W);
    MLV_clear_window(MLV_COLOR_BLACK);
    for (int i = 0; i < nbp; i++) {
        afficherParticle(&p[i]);
    }
    afficherQuadtree(qd, W, wmin);

    MLV_actualise_window();
    MLV_update_window();
    MLV_wait_event(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();

    freeQuadtree(qd);
    free(p);
    free(lstCell);
    return 0;
}
