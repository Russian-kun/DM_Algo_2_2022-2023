#include "Quadtree.h"
#include "affichage.h"
#include <time.h>

// TODO placement a la souris (loop click, menu avec option de generation, touche pour quitter)
int main(int argc, char* argv[]) {
    int puis = 9;
    int W = pow(2, puis), wmin = 2, kp = 2;
    int nbp = 200;
    Cell* lstCell = NULL;
    srand(time(NULL));
    Quadtree qt = initQuadtree(W, wmin);
    Particle* p = generateParticles(nbp, &lstCell, W);
    addParticlesQuadtree(qt, p, lstCell, nbp, kp);

    MLV_create_window("Quadtree", "Quadtree", W, W);
    MLV_clear_window(MLV_COLOR_BLACK);
    for (int i = 0; i < nbp; i++) {
        afficherParticle(p[i]);
    }
    afficherQuadtree(qt, W, wmin);

    MLV_actualise_window();
    MLV_update_window();
    MLV_wait_event(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();

    freeQuadtree(qt);
    free(p);
    free(lstCell);
    return 0;
}
