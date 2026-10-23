/** @file saisie.h @brief Lecture de stdin et signalement des saisies invalides. */
#ifndef MORPION_SAISIE_H
#define MORPION_SAISIE_H
#include "types.h"

/** @brief Résultat de lecture du format d'un coup, avant contrôle du plateau. */
enum LectureCoup {
  FIN_SAISIE, /**< Aucun caractère disponible avant une nouvelle ligne. */
  COUP_LU, /**< Deux entiers ont été lus ; leurs limites restent à contrôler. */
  FORMAT_INVALIDE /**< Ligne vide, incomplète ou contenant d'autres éléments. */
};

/** @brief Réponse à la proposition de nouvelle partie. */
enum ChoixRejeu {
  ARRETER, /**< Réponse n/N. */
  REJOUER, /**< Réponse o/O. */
  REJEU_INTERROMPU /**< Fin d'entrée avant une réponse valide. */
};

/** @brief Reconnaît les blancs acceptés à l'intérieur d'une ligne.
 * @param caractere Caractère lu avec getchar, ou EOF.
 * @return 1 pour espace, tabulation ou retour chariot, 0 sinon.
 * Le saut de ligne termine la saisie et n'est pas un séparateur interne. */
int estSeparateur(int caractere);

/** @brief Lit un entier sans signe à partir d'un caractère déjà disponible.
 * Saute les séparateurs internes et plafonne la valeur à TAILLE + 1.
 * @pre caractere désigne un entier accessible contenant le caractère courant.
 * @param caractere Adresse du caractère courant ; reçoit le premier caractère
 * non numérique après la coordonnée, ou la fin de ligne/EOF.
 * @return Valeur plafonnée, ou -1 si aucun chiffre n'a été lu.
 * La fonction ne franchit pas la fin de ligne. */
int lireCoordonnee(int *caractere);

/** @brief Demande un mot de 1 à 63 octets et consomme le reste de sa ligne.
 * @pre joueur désigne un joueur accessible en écriture ; numero vaut 1 ou 2.
 * @param joueur Joueur dont le nom est rempli.
 * @param numero Numéro affiché.
 * @return 1 si le nom est accepté, 0 à EOF. */
int demanderNom(struct Joueur *joueur, int numero);

/** @brief Lit deux entiers sans signe, séparés par des blancs, sur une ligne.
 * Les valeurs trop grandes sont plafonnées à TAILLE + 1, sans débordement.
 * @pre coup désigne une structure accessible en écriture.
 * @param coup Coordonnées remplies seulement si le format est correct.
 * @return COUP_LU si correct, FORMAT_INVALIDE sinon, FIN_SAISIE à EOF avant
 * la ligne. Toute la ligne est consommée, même après une erreur. */
enum LectureCoup lireCoup(struct Coup *coup);

/** @brief Demande o/n ; recommence après une réponse invalide.
 * @return REJOUER pour oui, ARRETER pour non, REJEU_INTERROMPU à EOF. */
enum ChoixRejeu demanderRejouer(void);
#endif
