#ifndef QUADTREE_H
#define QUADTREE_H

#include "Cell.h"

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
 * @param qt Quadtree
 * @param cell Cellule à ajouter
 * @param kp Nombre maximal de particules dans une feuille
 */
void addParticle(Quadtree qt, Cell *cell, int kp);

// Quadtree *FindContainingQuadtree(Quadtree *qt, Cell *cellule);

/**
 * @brief Retire une cellule du quadtree
 *
 * @param qt Quadtree
 * @param cellule Cellule à retirer
 * @return int
 */
int RemoveFromQuadtree(Quadtree *qt, Cell *cellule);

/**
 * @brief Cherche une cellule dans le quadtree et ses fils et la retire
 * si elle est trouvée. Retourne 1 si la cellule a été trouvée, 0 sinon.
 *
 * @param qt Quadtree
 * @param cellule Cellule à chercher
 * @param kp Nombre maximal de particules dans une feuille
 * @return int
 */
int FindAndRemoveCell(Quadtree *qt, Cell *cellule, int kp);

/**
 * @brief Fusionne les fils du quadtree
 *
 * @param qt Quadtree
 */
void FusionneFeuilles(Quadtree *qt);

#endif