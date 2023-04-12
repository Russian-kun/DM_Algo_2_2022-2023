#include "affichage.h"

/**
 * @brief Sous-fonction récursive d'affichage d'un quadtree
 * Affiche les noeuds de la quadtree en fonction du nombre de particules qu'ils contiennent
 *
 * @param qt
 * @param W
 * @param wmin
 */
void afficherQuadtreeRec(Quadtree qt, int W, int wmin) {
    if (qt == NULL) return;
    if (qt->height < wmin && qt->plist != NULL) {
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_RED);
        return;
    }
    if (qt->plist != NULL) {
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_rgba(100 + 12 * qt->nbp, 50, 50 + 15 * qt->nbp, 40));
        if (qt->nbp > 10) {
            fprintf(stderr, "\nErreur: Tentative d'affichage d'un noeud avec plus de 10 particules\nnbp: %d", qt->nbp);
        }
        return;
    }
    afficherQuadtreeRec(qt->nw, W, wmin);
    afficherQuadtreeRec(qt->ne, W, wmin);
    afficherQuadtreeRec(qt->sw, W, wmin);
    afficherQuadtreeRec(qt->se, W, wmin);
}

void afficherQuadtree(Quadtree qt, int W, int wmin) {
    afficherQuadtreeRec(qt, W, wmin);
}

void afficherParticle(Particle p) {
    MLV_draw_filled_circle(p.x, p.y, 1, MLV_COLOR_BLUE);
}