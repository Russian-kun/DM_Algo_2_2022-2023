#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/// @brief Structure de particule
typedef struct _particule_t {
    int x, y;    // coordonnée y de la particule
    int vx, vy;  // vitesse en y de la particule (optionnel)
} Particle;

/// @brief Structure de cellule de liste chaînée
typedef struct _cell_ {
    Particle *p;          // pointeur vers la particule
    struct _cell_ *next;  // pointeur vers la cellule suivante dans la liste
} Cell;

/// @brief Structure de nœud de quadtree
typedef struct _noeud_ {
    struct _noeud_ *nw, *ne, *sw, *se;  // pointeur vers les nœuds fils
    int x, y;                           // coordonnées du coin supérieur gauche du nœud
    int width, height;                  // Dimensions du nœud
    int nbp;                            // nombre de particules dans le nœud
    Cell *plist;                        // pointeur vers la liste chaînée de particules dans le nœud (NULL si nœud interne)
} Noeud, *TasNoeuds, *Quadtree;

Particle *initParticles(int nbp);

Quadtree initQuadtree(int W, int wmin);

void freeQuadtree(Quadtree qt);

Particle *generateParticles(int nbp, Cell **lst);

void addParticlesQuadtree(Quadtree qt, Particle *p, Cell *cell, int nbp, int kp);

Quadtree findLeaf(Quadtree qt, Particle *p);

void addParticle(Quadtree qtree, Cell *cell, int kp);

#endif