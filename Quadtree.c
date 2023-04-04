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

// Créer une nouvelle cellule avec une particule
Cell* createCell(Particle* p) {
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    if (newCell == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer de la mémoire pour une nouvelle cellule.\n");
        exit(EXIT_FAILURE);
    }
    newCell->p = p;
    newCell->next = NULL;
    return newCell;
}

/**
 * @brief Trouve la feuille du Quadtree qui contient la particule donnée
 *
 * @param qt Pointeur vers la racine du Quadtree
 * @param p Pointeur vers la particule à chercher
 * @return Quadtree Pointeur vers la feuille qui contient la particule, ou NULL si elle n'est pas dans le Quadtree
 */
Quadtree findLeaf(Quadtree qt, Particle* p) {
    // Si le Quadtree est vide, il n'y a pas de feuille contenant la particule
    if (qt == NULL) {
        return NULL;
    }
    // Si le Quadtree est une feuille, vérifier si elle contient la particule
    if (qt->nbp > 0) {
        Cell* current = qt->plist;
        while (current != NULL) {
            if (current->p == p) {
                return qt;
            }
            current = current->next;
        }
        // La particule n'a pas été trouvée dans la feuille
        return NULL;
    }
    // Si le Quadtree n'est pas une feuille, récursivement chercher dans les sous-quadtrees
    Quadtree leaf;
    if (p->x < qt->x + qt->width / 2) {
        if (p->y < qt->y + qt->height / 2) {
            leaf = findLeaf(qt->nw, p);
        } else {
            leaf = findLeaf(qt->sw, p);
        }
    } else {
        if (p->y < qt->y + qt->height / 2) {
            leaf = findLeaf(qt->ne, p);
        } else {
            leaf = findLeaf(qt->se, p);
        }
    }
    return leaf;
}

// Ajouter une particule dans la liste de cellules
void addParticle(Quadtree qtree, Particle* p) {
    // Trouver la feuille où insérer la particule
    Noeud* feuille = findLeaf(qtree, p);
    // Ajouter la particule dans la liste de cellules de la feuille
    Cell* newCell = createCell(p);
    newCell->next = feuille->plist;
    feuille->plist = newCell;
    feuille->nbp++;
}

void initQuadtreeRec(Noeud* node, int wmin) {
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
    Noeud* nw = &node[1];
    nw->x = x;
    nw->y = y;
    nw->width = width;
    nw->height = height;
    nw->nbp = 0;

    Noeud* ne = &node[2];
    ne->x = x + width;
    ne->y = y;
    ne->width = width;
    ne->height = height;
    ne->nbp = 0;

    Noeud* sw = &node[3];
    sw->x = x;
    sw->y = y + height;
    sw->width = width;
    sw->height = height;
    sw->nbp = 0;

    Noeud* se = &node[4];
    se->x = x + width;
    se->y = y + height;
    se->width = width;
    se->height = height;
    se->nbp = 0;

    // Initialisation récursive des fils
    initQuadtreeRec(nw, wmin);
    initQuadtreeRec(ne, wmin);
    initQuadtreeRec(sw, wmin);
    initQuadtreeRec(se, wmin);

    // Initialisation des pointeurs vers les fils
    node->nw = nw;
    node->ne = ne;
    node->sw = sw;
    node->se = se;
}

void initCell(Noeud* node) {
    node->nw = NULL;
    node->ne = NULL;
    node->sw = NULL;
    node->se = NULL;
}

Quadtree initQuadtree(int W, int wmin) {
    // Calcul de la hauteur h du QuadTree
    int h = log2(W);

    // Allocation du tableau de noeuds
    int nbNodes = (int)pow(4, h + 1) / 3;
    Quadtree quadtree = (Quadtree)malloc(sizeof(Noeud) * nbNodes);

    // Initialisation de la racine
    Noeud* root = &quadtree[0];
    root->x = 0;
    root->y = 0;
    root->width = W;
    root->height = W;
    root->nbp = 0;
    root->plist = NULL;
    initCell(root);

    // Initialisation récursive des fils
    initQuadtreeRec(root, wmin);

    return quadtree;
}

void freeQuadtree(Quadtree qt) {
    free(qt);
}

Particle* generateParticles(int nbp) {
    Particle* particules = (Particle*)malloc(nbp * sizeof(Particle));
    for (int i = 0; i < nbp; i++) {
        int x = rand() % 512;
        int y = rand() % 512;
        particules[i] = *allouerParticle(x, y, 0, 0);
    }
    return particules;
}