#ifndef PARAM_H
#define PARAM_H

/**
 * @brief Interprete les paramètres de la ligne de commande
 *
 * @param argc
 * @param argv
 * @param nbp
 * @param help
 * @param W
 * @param wmin
 * @param kp
 */
void interpretParam(int argc, char* argv[], int* nbp, int* help, int W, int wmin, int kp);

#endif