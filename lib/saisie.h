/** @file saisie.h @brief Lecture de stdin et signalement des saisies invalides. */
#ifndef MORPION_SAISIE_H
#define MORPION_SAISIE_H
#include "types.h"
/** @brief Demande un mot de 1 à 63 octets et consomme le reste de sa ligne.
 * @param joueur Joueur dont le nom est rempli. @param numero Numéro affiché.
 * @return 1 si le nom est accepté, 0 à EOF. */
int demanderNom(struct Joueur *joueur, int numero);
/** @brief Lit deux entiers sans signe, séparés par des blancs, sur une ligne.
 * Les valeurs trop grandes sont plafonnées à TAILLE + 1, sans débordement.
 * @param coup Coordonnées remplies seulement si le format est correct.
 * @return 1 si correct, -1 si format invalide, 0 à EOF avant la ligne. */
int lireCoup(struct Coup *coup);
/** @brief Demande o/n ; recommence après une réponse invalide.
 * @return 1 pour rejouer, 0 pour terminer, -1 à EOF. */
int demanderRejouer(void);
#endif
