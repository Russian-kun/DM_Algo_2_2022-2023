# DM 2 Algo des Arbres

AOUDI Hedia<br>
BAILLARGEAU Axel

## Description

Ce projet a pour but de réaliser un algorithme Quadtree permettant de subdiviser une image en plusieurs zones de particules. Ce projet a été réalisé dans le cadre du cours d'Algorithmique des Arbres de l'Université Gustave Eiffel de Marne-la-Valle.

## Utilisation

Pour utiliser ce projet, il suffit de lancer compiler avec la commande `make` puis de lancer le programme avec la commande `./main`. Le programme va alors créer une fenêtre graphique et afficher un menu permettant de choisir le type de generation. En mode manuel, on peut cliquer sur la fenetre pour ajouter des particules. On peut choisir la taille de la fenetre, le nombre de points, le nombre de particles, le nombre maximum de particules par zone et le nombre de niveaux de profondeur au moment de l'execution en argument.

## Structure du projet

Le projet est composé de plusieurs fichiers:

- `main.c` : Fichier principal du projet, contient la fonction main
- `Cell.c` : Fichier contenant les fonctions de manipulation des cellules de particules
- `Cell.h` : Fichier contenant les prototypes des fonctions de manipulation des cellules
- `Quadtree.c` : Fichier contenant les fonctions de manipulation du quadtree
- `Quadtree.h` : Fichier contenant les prototypes des fonctions de manipulation du quadtree
- `param.c` : Fichier contenant les fonctions de manipulation des parametres
- `param.h` : Fichier contenant les prototypes des fonctions de manipulation des parametres
- `affichage.c` : Fichier contenant les fonctions d'affichage
- `affichage.h` : Fichier contenant les prototypes des fonctions d'affichage

## Documentation

La documentation du projet est disponible dans le dossier `docs` et peut être générée avec la commande `make docs` ou avec la commande `doxygen Doxyfile` dans le dossier racine.
