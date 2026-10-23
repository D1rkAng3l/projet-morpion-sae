/** @file affichage.h @brief Affichage de la partie sur stdout. */
#ifndef MORPION_AFFICHAGE_H
#define MORPION_AFFICHAGE_H
#include "types.h"
/** @brief Affiche le compteur et le plateau avec ses repères.
 * @pre partie désigne une partie initialisée et accessible en lecture.
 * @param partie Partie consultée sans modification. */
void afficherPartie(const struct Partie *partie);
/** @brief Nomme le vainqueur ou annonce le match nul.
 * @pre partie désigne une partie terminée et accessible ; en cas de victoire,
 * gagnant vaut 0 ou 1 et désigne un joueur dont le nom est terminé par le caractère nul.
 * @param partie Partie terminée dont le résultat est affiché. */
void afficherResultat(const struct Partie *partie);
#endif
