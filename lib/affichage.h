/** @file affichage.h @brief Affichage de la partie sur stdout. */
#ifndef MORPION_AFFICHAGE_H
#define MORPION_AFFICHAGE_H
#include "types.h"
/** @brief Affiche le compteur et le plateau avec ses repères.
 * @param partie Partie consultée sans modification. */
void afficherPartie(const struct Partie *partie);
/** @brief Nomme le vainqueur ou annonce le match nul.
 * @param partie Partie terminée dont le résultat est affiché. */
void afficherResultat(const struct Partie *partie);
#endif
