/** @file saisie.h @brief Saisies simples sur l'entrée standard. */
#ifndef MORPION_SAISIE_H
#define MORPION_SAISIE_H
#include "types.h"

/** @brief Consomme la fin de ligne et vérifie qu'elle ne contient que des blancs.
 * @return 1 si seuls des espaces, tabulations ou retours chariot restent, 0 sinon. */
int terminerLigne(void);
/** @brief Demande un nom sans espace, limité à 63 octets.
 * @pre joueur est accessible en écriture.
 * @param joueur Joueur dont le nom est rempli.
 * @param numero Numéro affiché.
 * @return 1 si le nom est lu, 0 si l'entrée est épuisée. */
int demanderNom(struct Joueur *joueur, int numero);
/** @brief Lit deux coordonnées à un chiffre avec scanf.
 * @pre coup est accessible en écriture.
 * @param coup Coordonnées lues, à contrôler avant de jouer.
 * @return 1 si deux chiffres sont lus sans texte supplémentaire, -1 si le
 * format est incorrect, 0 si aucune coordonnée n'est disponible à la fin de l'entrée.
 * Les blancs sont ignorés par scanf ; les valeurs restent à vérifier. */
int lireCoup(struct Coup *coup);
/** @brief Demande o/n et recommence après une réponse incorrecte.
 * @return 1 pour rejouer, 0 pour arrêter, -1 si l'entrée est épuisée. */
int demanderRejouer(void);
#endif
