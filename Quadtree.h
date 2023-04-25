#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/// @brief Structure de particule
typedef struct _particule_t {
    int x, y;    // coordonnée y de la particule
    int vx, vy;  // vitesse en y de la particule
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
    int nbp;                            // nombre de particules dans le nœud et ses fils
    Cell *plist;                        // pointeur vers la liste chaînée de particules dans le nœud (NULL si nœud interne)
} Noeud, *TasNoeuds, *Quadtree;

/**
 * @brief Initialise un quadtree
 *
 * @param W Cote du carre
 * @param wmin Taille minimale des feuilles
 * @return Quadtree
 */
Quadtree initQuadtree(int W, int wmin);

/**
 * @brief Libère la mémoire allouée pour un quadtree
 *
 * @param qt Quadtree
 */
void freeQuadtree(Quadtree qt);

/**
 * @brief Génère un tableau de particule ainsi que les cellule d'une
 * liste chaînée de particules
 *
 * @param nbp Nombre de particules
 * @param lst Pointeur vers la liste chaînée de cellules
 * @param W Cote du carre
 * @return Particle*
 */
Particle *generateParticles(int nbp, Cell **lst, int W);

/**
 * @brief Ajoute des particules dans un quadtree
 *
 * @param qt Quadtree
 * @param cell Tableau de cellules
 * @param nbp Nombre de particules
 * @param kp Nombre maximal de particules dans une feuille
 */
void addParticlesQuadtree(Quadtree qt, Cell *cell, int nbp, int kp);

/**
 * @brief Ajoute une particule dans un quadtree
 *
 * @param qtree
 * @param cell
 * @param kp
 */
void addParticle(Quadtree qtree, Cell *cell, int kp);

Quadtree *FindContainingQuadtree(Quadtree *qt, Cell *cellule);

int RemoveFromQuadtree(Quadtree *qt, Cell *cellule);

int FindAndRemoveCell(Quadtree *qt, Cell *cellule, int kp);

void updateQuadtree(Quadtree *qt, Cell *cellule, int kp);

Cell *getLastCell(Cell *cell);

#endif