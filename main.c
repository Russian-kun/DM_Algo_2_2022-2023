#include "Quadtree.h"
#include "affichage.h"
#include <time.h>

// TODO placement a la souris (loop click, menu avec option de generation, touche pour quitter)
int main(int argc, char* argv[]) {
    int ret = 0, placement = 0, clicx, clicy;
    int puis = 9;
    int W = pow(2, puis), wmin = 2, kp = 2;
    MLV_create_window("Quadtree", "Quadtree", W, W);
    MLV_Keyboard_button but;
    while (ret == 0) {
        MLV_clear_window(MLV_COLOR_BLACK);
        afficherMenu(placement, W, W);
        MLV_actualise_window();
        MLV_update_window();
        MLV_wait_keyboard_or_mouse(&but, NULL, NULL, &clicx, &clicy);
        // MLV_wait_mouse(&clicx, &clicy);
        ret = clicMenu(clicx, clicy);
        if (ret == 2) {
            placement = (placement + 1) % 2;
        }
        if (but == MLV_KEYBOARD_ESCAPE) {
            ret = 3;
        }
    }
    if (ret == 3) {
        MLV_free_window();
        return 0;
    }

    int nbp = 200;
    Cell* lstCell = NULL;
    srand(time(NULL));
    Quadtree qt = initQuadtree(W, wmin);
    if (placement) {
        Particle* p = generateParticles(nbp, &lstCell, W);
        addParticlesQuadtree(qt, p, lstCell, nbp, kp);

        MLV_clear_window(MLV_COLOR_BLACK);
        for (int i = 0; i < nbp; i++) {
            afficherParticle(p[i]);
        }
        afficherQuadtree(qt, W, wmin);
        free(p);
    }

    MLV_actualise_window();
    MLV_update_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();

    freeQuadtree(qt);
    free(lstCell);
    return 0;
}
