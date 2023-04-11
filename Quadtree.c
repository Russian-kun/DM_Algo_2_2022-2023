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
    if (qt->height == 1 && qt->width == 1)
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
            prev = cell;
            cell = cell->next;
            break;
        }
    }
}

// Ajouter une particule dans la liste de cellules
void addParticle(Quadtree qtree, Cell* cell, int kp) {
    Particle* p = cell->p;

    // Ajouter la particule dans la liste de cellules de la feuille
    Cell* newCell = cell;
    newCell->next = qtree->plist;
    qtree->plist = newCell;
    qtree->nbp++;
    if (sature(qtree, kp)) {
        // Si la feuille est saturée, on la divise
        split(qtree, kp);
    }
}

void initQuadtreeRec(Noeud* node, int wmin, int niveau) {
    // Si la résolution minimale est atteinte, on arrête la récursion
    if (node->width <= wmin) {
        return;
    }

    // Calcul des coordonnées et des dimensions des sous-zones
    int x = node->x;
    int y = node->y;
    int width = node->width / 2;
    int height = node->height / 2;

    // Initialisation des fils nord-ouest, nord-est, sud-ouest et sud-est
    Noeud* nw = &node[(int)pow(4, niveau) + 1];
    nw->x = x;
    nw->y = y;
    nw->width = width;
    nw->height = height;
    nw->nbp = 0;
    initQuadtreeRec(nw, wmin, niveau + 1);

    Noeud* ne = nw + 1;  // &node[pow(4, niveau) + 1];
    ne->x = x + width;
    ne->y = y;
    ne->width = width;
    ne->height = height;
    ne->nbp = 0;
    initQuadtreeRec(ne, wmin, niveau + 1);

    Noeud* sw = ne + 1;  // &node[pow(4, niveau) + 2]
    sw->x = x;
    sw->y = y + height;
    sw->width = width;
    sw->height = height;
    sw->nbp = 0;
    initQuadtreeRec(sw, wmin, niveau + 1);

    Noeud* se = sw + 1;  // &node[pow(4, niveau) + 3]
    se->x = x + width;
    se->y = y + height;
    se->width = width;
    se->height = height;
    se->nbp = 0;
    initQuadtreeRec(se, wmin, niveau + 1);

    // Initialisation des pointeurs vers les fils
    node->nw = nw;
    node->ne = ne;
    node->sw = sw;
    node->se = se;
}

Quadtree initQuadtree(int W, int wmin) {
    // Calcul de la hauteur h du QuadTree
    int h = log2(W);

    // Allocation du tableau de noeuds
    int nbNodes = (int)pow(4, h + 1) / 3;
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
    initQuadtreeRec(root, wmin, 0);

    return quadtree;
}

void freeQuadtree(Quadtree qt) {
    free(qt);
}

Particle* generateParticles(int nbp, Cell** cell) {
    Particle* particules = (Particle*)malloc(nbp * sizeof(Particle));
    *cell = calloc(nbp, sizeof(Cell));
    for (int i = 0; i < nbp; i++) {
        int x = rand() % 512;
        int y = rand() % 512;
        particules[i] = (Particle){x, y, 0, 0};
        (*cell)[i] = (Cell){&particules[i], NULL};
    }
    return particules;
}

void addParticlesQuadtree(Quadtree qt, Particle* p, Cell* cell, int nbp, int kp) {
    int i;
    qt->plist = &cell[0];
    qt->nbp++;
    for (i = 1; i < nbp; i++) {
        addParticle(qt, &cell[i], kp);
    }
}