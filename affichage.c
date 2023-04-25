#include "affichage.h"
#include "MLV/MLV_all.h"

/**
 * @brief Sous-fonction récursive d'affichage d'un quadtree
 * Affiche les noeuds de la quadtree en fonction du nombre de particules qu'ils contiennent
 *
 * @param qt Pointeur vers le nœud courant
 * @param W Largeur de la fenetre
 * @param wmin Largeur minimale d'un nœud
 */
void afficherQuadtreeRec(Quadtree qt, int W, int wmin) {
    if (qt == NULL || qt->nbp == 0) return;
    if (qt->height < wmin && qt->plist != NULL) {
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_RED);
        return;
    }
    if (qt->plist != NULL) {
        MLV_draw_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(qt->x, qt->y, qt->height, qt->height, MLV_rgba(150 + 12 * qt->nbp, 50, 100 + 15 * qt->nbp, 60));
        MLV_actualise_window();
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

/**
 * @brief Macro pour dessiner un texte centré sur un point
 *
 * @param x Coordonnée x du point
 * @param y Coordonnée y du point
 * @param width Largeur de la boite
 * @param height Hauteur de la boite
 * @param text Texte à afficher
 * @param size_interligne Taille de l'interligne
 * @param border_color Couleur de la bordure
 * @param text_color Couleur du texte
 * @param background_color Couleur du fond
 * @param text_justification Justification du texte
 * @param horizontal_position Positionnement horizontal
 * @param vertical_position Positionnement vertical
 */
void MLV_draw_text_box_centered(int x, int y, int width, int height, const char* text, int size_interligne, MLV_Color border_color, MLV_Color text_color, MLV_Color background_color, MLV_Text_justification text_justification, MLV_Horizontal_position horizontal_position, MLV_Vertical_position vertical_position) {
    MLV_draw_text_box(x - width / 2, y - height / 2, width, height, text, size_interligne, border_color, text_color, background_color, text_justification, horizontal_position, vertical_position);
}

void afficherMenu(int choix, int X, int Y) {
    char* text[2] = {"Placement Manuel", "Placement Automatique"};
    int center[2] = {X / 2, Y / 2};
    MLV_draw_text_box_centered(center[0], center[1] - 50, 200, 50, text[choix], 0, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box_centered(center[0], center[1] + 50, 200, 50, "Lancer", 0, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box_centered(center[0], center[1] + 150, 200, 50, "Quitter", 0, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

int clicMenu(int x, int y) {
    int X = MLV_get_window_width();
    int Y = MLV_get_window_height();
    int center[2] = {X / 2, Y / 2};
    if (x > center[0] - 100 && x < center[0] + 100) {
        if (y > center[1] - 50 && y < center[1]) {
            return 2;
        }
        if (y > center[1] + 50 && y < center[1] + 100) {
            return 1;
        }
        if (y > center[1] + 150 && y < center[1] + 200) {
            return 3;
        }
    }
    return 0;
}