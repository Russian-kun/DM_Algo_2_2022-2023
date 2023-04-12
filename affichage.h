#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "MLV/MLV_all.h"
#include "Quadtree.h"

/**
 * @brief Affiche un quadtree
 *
 * @param qt
 * @param W
 * @param wmin
 */
void afficherQuadtree(Quadtree qt, int W, int wmin);

/**
 * @brief Affiche une particule
 *
 * @param p
 */
void afficherParticle(Particle p);

#endif