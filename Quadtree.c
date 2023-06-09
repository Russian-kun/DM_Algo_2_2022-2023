#include "Quadtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief Sous-fonction de initQuadtree
 *
 * @param node Pointeur vers le nœud courant
 * @param wmin Résolution minimale
 * @param niveau Niveau courant
 * @param position Position du nœud courant
 */
static void initQuadtreeRec(Noeud* node, int wmin, int niveau, int position) {
    // Si la résolution minimale est atteinte, on arrête la récursion
    if (node->width <= wmin) {
        return;
    }

    // Calcul des coordonnées et des dimensions des sous-zones
    int x = node->x;
    int y = node->y;
    int width = node->width / 2;
    int height = width;
    // Position correspond a la position du pere

    // Calcul du nombre de frères
    int nb_frere = pow(4, niveau);
    // Calcul de la position du premier fils
    int pos_premier_fils = nb_frere * 4 / 3;
    // Calcul de la position du premier frère
    int pos_premier_frere = nb_frere / 3;
    // Calcul de la position du frère
    int distance_frere = position - pos_premier_frere;

    int pos_actuelle = pos_premier_fils + distance_frere * 4;

    int new_pos = pos_actuelle;

    // Initialisation des fils nord-ouest, nord-est, sud-ouest et sud-est
    node->nw = &node[new_pos];
    node->nw->x = x;
    node->nw->y = y;
    node->nw->width = width;
    node->nw->height = height;
    node->nw->nbp = 0;
    initQuadtreeRec(node->nw, wmin, niveau + 1, new_pos);

    node->ne = node->nw + 1;
    node->ne->x = x + width;
    node->ne->y = y;
    node->ne->width = width;
    node->ne->height = height;
    node->ne->nbp = 0;
    initQuadtreeRec(node->ne, wmin, niveau + 1, new_pos + 1);

    node->sw = node->ne + 1;
    node->sw->x = x;
    node->sw->y = y + height;
    node->sw->width = width;
    node->sw->height = height;
    node->sw->nbp = 0;
    initQuadtreeRec(node->sw, wmin, niveau + 1, new_pos + 2);

    node->se = node->sw + 1;
    node->se->x = x + width;
    node->se->y = y + height;
    node->se->width = width;
    node->se->height = height;
    node->se->nbp = 0;
    initQuadtreeRec(node->se, wmin, niveau + 1, new_pos + 3);
}

Quadtree initQuadtree(int W, int wmin) {
    // Allocation du tableau de noeuds
    int nbNodes = pow(4, log2(W) + 1);  // W * W * 4;
    Quadtree quadtree = calloc(nbNodes, sizeof(Noeud));

    // Initialisation de la racine
    Noeud* root = &quadtree[0];
    root->x = 0;
    root->y = 0;
    root->width = W;
    root->height = W;
    root->nbp = 0;
    root->plist = NULL;

    // Initialisation récursive des fils
    initQuadtreeRec(root, wmin, 0, 1);

    return quadtree;
}

void freeQuadtree(Quadtree qt) {
    free(qt);
}

/**
 * @brief Verifie si un quadtree est plein
 *
 * @param qt Pointeur vers le nœud courant
 * @param kp Nombre de particules maximum par nœud
 * @return int
 */
static int sature(Quadtree qt, int kp) {
    return qt->nbp >= kp;
}

/**
 * @brief Verifie si une particule est comprise dans
 * les dimensions d'un quadtree
 *
 * @param qt Pointeur vers le nœud courant
 * @param p Pointeur vers la particule
 * @return int
 */
static int isInQuadtree(Quadtree qt, Particle* p) {
    if (qt == NULL) return 0;
    return p->x >= qt->x && p->x < qt->x + qt->width && p->y >= qt->y && p->y < qt->y + qt->height;
}

/**
 * @brief Distribue les particules d'une liste chaînée dans les fils d'un nœud
 *
 * @param qt Pointeur vers le nœud courant
 * @param kp Nombre de particules maximum par nœud
 */
static void split(Quadtree qt, int kp) {
    if (qt->nw == NULL || qt->ne == NULL || qt->sw == NULL || qt->se == NULL)
        return;
    Cell* cell = qt->plist;
    Cell* prev = NULL;
    while (cell != NULL) {
        // On vérifie si la particule est dans chacun des fils
        if (isInQuadtree(qt->nw, cell->p)) {
            Cell* tmp = cell;
            // On supprime la cellule de la liste chaînée
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            // On ajoute la particule dans le fils correspondant
            addParticle(qt->nw, tmp, kp);
        } else if (isInQuadtree(qt->ne, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->ne, tmp, kp);
        } else if (isInQuadtree(qt->sw, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->sw, tmp, kp);
        } else if (isInQuadtree(qt->se, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->se, tmp, kp);
        } else {
            if (qt->nw != NULL) {
                fprintf(stderr, "\nErreur: Particule non répartie dans le quadtree\n");
                fprintf(stderr, "x: %d, y: %d\n", cell->p->x, cell->p->y);
                fprintf(stderr, "Quadtree: x: %d, y: %d, width: %d, height: %d\n", qt->x, qt->y, qt->width, qt->height);
            }
            prev = cell;
            cell = cell->next;
        }
    }
}

void addParticle(Quadtree qt, Cell* cell, int kp) {
    // Ajouter la particule dans la liste de cellules de la feuille
    Cell* newCell = cell;
    newCell->next = qt->plist;
    qt->plist = newCell;
    qt->nbp++;
    if (sature(qt, kp)) {
        // Si la feuille est saturée, on la divise
        split(qt, kp);
    }
}

/**
 * @brief Verifie si une particule est dans la liste chaînée d'un quadtree
 *
 * @param qt
 * @param p
 * @return int
 */
static int isInPlist(Quadtree qt, Cell* cellule) {
    Cell* cell = qt->plist;
    while (cell != NULL) {
        if (cell == cellule) {
            return 1;
        }
        if (cell == cell->next) {
            printf("Erreur de chainage : cell == cell->next\n");
            return 1;
        }
        cell = cell->next;
    }
    return 0;
}

void addParticlesQuadtree(Quadtree qt, Cell* cell, int nbp, int kp) {
    int i;
    for (i = 0; i < nbp; i++) {
        addParticle(qt, &cell[i], kp);
    }
}

int RemoveFromQuadtree(Quadtree* qt, Cell* cellule) {
    Cell* cell = (*qt)->plist;
    Cell* prev = NULL;
    while (cell != NULL) {
        if (cell == cellule) {
            // On supprime la cellule de la liste chaînée
            if (prev == NULL) {
                (*qt)->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            (*qt)->nbp--;
            return 1;
        }
        prev = cell;
        cell = cell->next;
    }
    return 0;
}

// Quadtree* FindContainingQuadtree(Quadtree* qt, Cell* cellule) {
//     if (isInPlist(*qt, cellule)) {
//         return qt;
//     }
//     if (isInQuadtree((*qt)->nw, cellule->p)) {
//         Quadtree* tmp = FindContainingQuadtree(&(*qt)->nw, cellule);
//         if (tmp != NULL) {
//             return tmp;
//         }
//     }
//     if (isInQuadtree((*qt)->ne, cellule->p)) {
//         Quadtree* tmp = FindContainingQuadtree(&(*qt)->ne, cellule);
//         if (tmp != NULL) {
//             return tmp;
//         }
//     }
//     if (isInQuadtree((*qt)->sw, cellule->p)) {
//         Quadtree* tmp = FindContainingQuadtree(&(*qt)->sw, cellule);
//         if (tmp != NULL) {
//             return tmp;
//         }
//     }
//     if (isInQuadtree((*qt)->se, cellule->p)) {
//         Quadtree* tmp = FindContainingQuadtree(&(*qt)->se, cellule);
//         if (tmp != NULL) {
//             return tmp;
//         }
//     }
//     return NULL;
// }

int FindAndRemoveCell(Quadtree* qt, Cell* cellule, int kp) {
    if (isInPlist(*qt, cellule)) {
        RemoveFromQuadtree(qt, cellule);
        return 1;
    }
    if (isInQuadtree((*qt)->nw, cellule->p)) {
        int tmp = FindAndRemoveCell(&(*qt)->nw, cellule, kp);
        if (tmp != 0) {
            (*qt)->nbp--;
            if ((*qt)->nbp < kp) {
                FusionneFeuilles(qt);
            }
            return tmp;
        }
    } else if (isInQuadtree((*qt)->ne, cellule->p)) {
        int tmp = FindAndRemoveCell(&(*qt)->ne, cellule, kp);
        if (tmp != 0) {
            (*qt)->nbp--;
            if ((*qt)->nbp < kp) {
                FusionneFeuilles(qt);
            }
            return tmp;
        }
    } else if (isInQuadtree((*qt)->sw, cellule->p)) {
        int tmp = FindAndRemoveCell(&(*qt)->sw, cellule, kp);
        if (tmp != 0) {
            (*qt)->nbp--;
            if ((*qt)->nbp < kp) {
                FusionneFeuilles(qt);
            }
            return tmp;
        }
    } else if (isInQuadtree((*qt)->se, cellule->p)) {
        int tmp = FindAndRemoveCell(&(*qt)->se, cellule, kp);
        if (tmp != 0) {
            (*qt)->nbp--;
            if ((*qt)->nbp < kp) {
                FusionneFeuilles(qt);
            }
            return tmp;
        }
    }
    return 0;
}

void FusionneFeuilles(Quadtree* qt) {
    Quadtree* fils[4] = {&(*qt)->nw, &(*qt)->ne, &(*qt)->sw, &(*qt)->se};
    int i = 0;
    for (i = 0; i < 4; i++) {
        if ((*fils[i])->nbp == 0)
            continue;

        Cell* last = getLastCell((*qt)->plist);
        // On ajoute la liste chaînée de la feuille au père
        if (last != NULL)
            last->next = (*fils[i])->plist;
        else
            (*qt)->plist = (*fils[i])->plist;
        // On supprime la liste chaînée de la feuille
        (*fils[i])->plist = NULL;
        (*fils[i])->nbp = 0;
    }
}
