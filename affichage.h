#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Quadtree.h"

/**
 * @brief Affiche un quadtree
 *
 * @param qt Quadtree
 * @param W Cote du carre
 * @param wmin Taille minimale des feuilles
 */
void afficherQuadtree(Quadtree qt, int W, int wmin);

/**
 * @brief Affiche une particule
 *
 * @param p Particule
 */
void afficherParticle(Particle p);

/**
 * @brief Affiche le menu centree dans la fenetre
 * Pour l'instant, il n'y a que le placement des particules
 * en automatique ou manuel
 *
 * @param choix 0 pour automatique, 1 pour manuel
 * @param X Largeur de la fenetre
 * @param Y Hauteur de la fenetre
 */
void afficherMenu(int choix, int X, int Y);

/**
 * @brief Renvoie le choix du menu en fonction du clic
 *
 * @param x Coordonnée x du clic
 * @param y Coordonnée y du clic
 * @return int
 */
int clicMenu(int x, int y);

#endif