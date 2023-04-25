#ifndef CELL_H
#define CELL_H

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

Cell *getLastCell(Cell *cell);

#endif