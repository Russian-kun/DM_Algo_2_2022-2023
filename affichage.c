#include "affichage.h"

void afficherQuadtreeRec(Quadtree qt, int W, int wmin) {
    if (qt == NULL) return;
    if (qt->height < wmin) {
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_RED);
        return;
    }
    if (qt->nbp != 0)
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_WHITE);
    afficherQuadtreeRec(qt->nw, W, wmin);
    afficherQuadtreeRec(qt->ne, W, wmin);
    afficherQuadtreeRec(qt->sw, W, wmin);
    afficherQuadtreeRec(qt->se, W, wmin);
}

void afficherQuadtree(Quadtree qt, int W, int wmin) {
    afficherQuadtreeRec(qt, W, wmin);
}

void afficherParticle(Particle* p) {
    MLV_draw_filled_circle(p->x, p->y, 1, MLV_COLOR_BLUE);
}