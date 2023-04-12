#include "Quadtree.h"

Particle* allouerParticle(int x, int y, int vx, int vy) {
    Particle* p = (Particle*)malloc(sizeof(Particle));
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    return p;
}

Particle* initParticles(int nbp) {
    Particle* particules = (Particle*)malloc(nbp * sizeof(Particle));
    for (int i = 0; i < nbp; i++) {
        int x = rand() % 512;
        int y = rand() % 512;
        particules[i] = *allouerParticle(x, y, 0, 0);
    }
    return particules;
}

int isLeaf(Quadtree qt) {
    return qt->plist != NULL;
}

int isInPlist(Quadtree qt, Particle* p) {
    Cell* cell = qt->plist;
    while (cell != NULL) {
        if (cell->p == p) {
            return 1;
        }
        cell = cell->next;
    }
    return 0;
}

int sature(Quadtree qt, int kp) {
    return qt->nbp >= kp;
}

int isInQuadtree(Quadtree qt, Particle* p) {
    if (qt == NULL) return 0;
    return p->x >= qt->x && p->x < qt->x + qt->width && p->y >= qt->y && p->y < qt->y + qt->height;
}

/**
 * @brief Distribue les particules d'une liste chaînée dans les fils d'un nœud
 *
 */
void split(Quadtree qt, int kp) {
    if (qt->nw == NULL || qt->ne == NULL || qt->sw == NULL || qt->se == NULL)
        return;
    Cell* cell = qt->plist;
    Cell* prev = NULL;
    while (cell != NULL) {
        if (isInQuadtree(qt->nw, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->nw, tmp, kp);
            // free(tmp);
        } else if (isInQuadtree(qt->ne, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->ne, tmp, kp);
            // free(tmp);
        } else if (isInQuadtree(qt->sw, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->sw, tmp, kp);
            // free(tmp);
        } else if (isInQuadtree(qt->se, cell->p)) {
            Cell* tmp = cell;
            if (prev == NULL) {
                qt->plist = cell->next;
            } else {
                prev->next = cell->next;
            }
            cell = cell->next;
            addParticle(qt->se, tmp, kp);
            // free(tmp);
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

// Ajouter une particule dans la liste de cellules
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

void initQuadtreeRec(Noeud* node, int wmin, int niveau, int position) {
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
    // Calcul de la hauteur h du QuadTree
    // int h = log2(W);

    // Allocation du tableau de noeuds
    // int nbNodes = (int)pow(4, h);
    int nbNodes = W * W * 4;
    // int nbNodes = h;
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

void addParticlesQuadtree(Quadtree qt, Particle* p, Cell* cell, int nbp, int kp) {
    int i;
    for (i = 0; i < nbp; i++) {
        addParticle(qt, &cell[i], kp);
    }
}