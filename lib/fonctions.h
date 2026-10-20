/** @file fonctions.h @brief Déroulement d'une partie complète. */
#ifndef MORPION_FONCTIONS_H
#define MORPION_FONCTIONS_H
#include "types.h"
/** @brief Réinitialise puis conduit une partie jusqu'au résultat ou à EOF.
 * @param partie Partie contenant les noms déjà saisis.
 * @return 1 si terminée normalement, 0 si l'entrée est interrompue. */
int jouerPartie(struct Partie *partie);
#endif
