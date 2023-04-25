#include "Quadtree.h"
#include "affichage.h"
#include "MLV/MLV_all.h"
#include <time.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int ret = 0, placement = 0;
    int clicx, clicy;
    // Nombre de particules
    int nbp = 200;
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
            ret = 0;
        }
        if (but == MLV_KEYBOARD_ESCAPE) {
            ret = 3;
        }
    }
    if (ret == 3) {
        MLV_free_window();
        return 0;
    }

    // Tableau de cellules
    Cell* lstCell = NULL;
    srand(time(NULL));
    Quadtree qt = initQuadtree(W, wmin);
    Particle* p = generateParticles(nbp, &lstCell, W);
    // Generation aleatoire
    if (placement) {
        addParticlesQuadtree(qt, lstCell, nbp, kp);

        MLV_clear_window(MLV_COLOR_BLACK);
        for (int i = 0; i < nbp; i++) {
            afficherParticle(p[i]);
        }
        afficherQuadtree(qt, W, wmin);
        free(p);
    }
    // Placement Manuel
    else {
        int curr_part = 0;
        while (curr_part < nbp) {
            MLV_clear_window(MLV_COLOR_BLACK);
            for (int i = 0; i < curr_part; i++) {
                afficherParticle(p[i]);
                MLV_actualise_window();
            }
            afficherQuadtree(qt, W, wmin);
            MLV_actualise_window();
            MLV_update_window();
            MLV_wait_keyboard_or_mouse(&but, NULL, NULL, &clicx, &clicy);
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
                p[curr_part].x = clicx;
                p[curr_part].y = clicy;
                addParticle(qt, &lstCell[curr_part], kp);
                curr_part++;
            } else if (but == MLV_KEYBOARD_ESCAPE) {
                curr_part = nbp;
            } else if (but == MLV_KEYBOARD_BACKSPACE) {
                if (curr_part > 0) {
                    ret = FindAndRemoveCell(&qt, &lstCell[curr_part - 1], kp);
                    curr_part--;
                }
            } else if (but == MLV_KEYBOARD_r) {
                p[curr_part].x = rand() % W;
                p[curr_part].y = rand() % W;
                addParticle(qt, &lstCell[curr_part], kp);
                curr_part++;
            }
        }
    }

    MLV_actualise_window();
    MLV_update_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();

    freeQuadtree(qt);
    free(lstCell);
    return 0;
}
