# DM_Algo_2_2022-2023

## Description

Ce dépôt contient le code pour le cours d'algorithmique de la décision à l'Université Gustave Eiffel de Marne-la-Vallée, en deuxieme année de license informatique.

## Installation

### Compilation

## Code

### ALIGN

Dans le contexte de la macro ALIGN(size), le "et binaire" est utilisé pour effacer les bits de poids faible qui ne sont pas alignés sur la taille d'alignement spécifiée. L'expression ~(ALIGNMENT - 1) calcule une valeur qui a des bits à 0 dans toutes les positions qui sont des multiples de la taille d'alignement moins un, et des bits à 1 dans toutes les autres positions. Par exemple, si la taille d'alignement est 8, alors ~(ALIGNMENT - 1) donne la valeur binaire 0xFFFFFFF8.

Ensuite, l'expression ((size) + (ALIGNMENT - 1)) ajoute la taille d'alignement moins un à la taille size, pour garantir que l'adresse résultante sera au moins un multiple de la taille d'alignement. Par exemple, si size est 13 et que la taille d'alignement est 8, alors ((size) + (ALIGNMENT - 1)) donne 20.

Finalement, l'opérateur "et binaire" est utilisé pour effacer les bits de poids faible qui ne sont pas alignés sur la taille d'alignement. L'expression ((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1) effectue un "et binaire" entre le résultat de l'addition et l'inverse de la taille d'alignement moins un, en produisant un résultat qui a des bits à 0 dans toutes les positions qui ne sont pas alignées sur la taille d'alignement, et des bits à 1 dans toutes les autres positions. Par exemple, si size est 13 et que la taille d'alignement est 8, alors ((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1) donne 16, car les bits de poids faible de 20 sont effacés par l'opération de "et binaire" avec 0xFFFFFFF8.

## Annexes

### Documentation

### Tests
