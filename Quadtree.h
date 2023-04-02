#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* En particulier nous limiterons ici les appels
aux fonctions de gestion demémoire (malloc/free)
au strict minimum. Les données de départ sont :
la taille initiale de la zone de travail :
    pour des raisons évidentes nous partirons
    d’une zone carrée dont la dimension (entière)
    est une puissance de 4: WxH=512x512 ou 1024x1024
    (ça correspond à despixels).
la taille minimale (taille d’unefeuille(wminxwmin),
arrêt de subdivision) sera elle aussi une puissance de 4
((1x1),(2x2),(4x4)...).
le nombre Np de particules peut quant à lui être
quelconque, de même que le nombre max. (Kp)
de particules contenu dans une feuille. Ces particules
seront stockées dans un tableau.
Le QuadTree sera toujours initialisé sous sa forme
complète, c’est à dire comme si il allait être
utilisé jusqu’à sa plus fine résolution (wmin=1).
On peut donc évaluer la taille mémoire nécessaire
et stocker le QuadTree sous la forme d’un tableau
de noeuds structuré comme un "tas d’ordre 4".
Les paramètres principaux sont donc W=2h et Np et
il n’y a que 2 allocations de mémoire à produire :
    le QuadTree et le tableau de particules (aucun
    noeuds ni aucune particule ne sera créé(e) ou
    détruit(e) en cours de route). Et en paramètres
    secondaires on fixera la taille minimale d’une
    feuille w min et le nombre maximal de particules
    qu’un noeud peut accueillir Kp. */

/* chaînage  des  particules: en parallèle du tableau de points, il sera nécessaire de maintenir unsystème dechaînagequi permettra d’accéder facilement à la liste des particules contenues dans unefeuille duQuadTree.  Les points pouvant théoriquement se déplacer, il peuvent changer denoeudduQuadTree. Et même si les points ne bougent pas, à l’initalisation du système ils sont intégrés un par undans leQuadTree. */

// Définition d'une particule
typedef struct _particule_t {
    int x, y;    // coordonnée y de la particule
    int vx, vy;  // vitesse en y de la particule (optionnel)
} Particle;

// Définition d'une cellule de liste chaînée de particules
typedef struct _cell_ {
    Particle *p;          // pointeur vers la particule
    struct _cell_ *next;  // pointeur vers la cellule suivante dans la liste
} Cell;

// Définition d'un nœud du QuadTree
typedef struct _noeud_ {
    struct _noeud_ *nw, *ne, *sw, *se;  // pointeur vers les nœuds fils
    int x, y;                           // coordonnées du coin supérieur gauche du nœud
    int width, height;                  // Dimensions du nœud
    int nbp;                            // nombre de particules dans le nœud
    Cell *plist;                        // pointeur vers la liste chaînée de particules dans le nœud (NULL si nœud interne)
} Noeud;

#endif