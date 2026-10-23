/** @file partie.h @brief Déroulement d'une partie complète. */
#ifndef MORPION_PARTIE_H
#define MORPION_PARTIE_H
#include "types.h"
/** @brief Réinitialise puis conduit une partie jusqu'au résultat ou à EOF.
 * @pre partie est accessible en écriture et contient deux noms terminés
 * par le caractère nul. Son plateau et ses compteurs seront réinitialisés.
 * @param partie Partie contenant les noms déjà saisis.
 * @return 1 si terminée normalement, 0 si l'entrée est interrompue. */
int jouerPartie(struct Partie *partie);
#endif
