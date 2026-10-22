/** @file plateau.h @brief Contrats de la logique du morpion, sans entrée-sortie. */
#ifndef MORPION_PLATEAU_H
#define MORPION_PLATEAU_H
#include "types.h"
/** @brief Vide le plateau et remet X au premier tour, sans effacer les noms.
 * @param partie Partie à réinitialiser. */
void initialiserPartie(struct Partie *partie);
/** @brief Contrôle les limites, l'état et l'occupation sans modifier la partie.
 * @param partie Partie à consulter. @param coup Case visée.
 * @return Motif du refus ou COUP_VALIDE. */
enum ControleCoup verifierCoup(const struct Partie *partie, struct Coup coup);
/** @brief Cherche un alignement de trois pions identiques non vides.
 * @param partie Partie à consulter. @return Indice du gagnant, ou -1. */
int chercherGagnant(const struct Partie *partie);
/** @brief Pose un coup valide et actualise le résultat.
 * La main passe seulement après un coup accepté si la partie continue.
 * Un coup refusé ne modifie aucune information.
 * @param partie Partie à modifier. @param coup Case visée.
 * @return Motif du refus ou COUP_VALIDE après placement. */
enum ControleCoup jouerCoup(struct Partie *partie, struct Coup coup);
#endif
