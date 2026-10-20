/** @file affichage.c @brief Présentation console indépendante des règles. */
#include "affichage.h"
#include <stdio.h>

/** @brief Affiche le compteur et le plateau avec ses repères.
 * @param partie Partie consultée sans modification. */
void afficherPartie(const struct Partie *partie) {
  printf("\nCoups poses : %d\n    ", partie->nombreCoups);
  for (int colonne = 0; colonne < TAILLE; colonne++) printf(" %2d ", colonne + 1);
  printf("\n");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("    ");
    for (int colonne = 0; colonne < TAILLE; colonne++) printf("+---");
    printf("+\n%3d ", ligne + 1);
    for (int colonne = 0; colonne < TAILLE; colonne++)
      printf("| %c ", partie->grille[ligne][colonne]);
    printf("|\n");
  }
  printf("    ");
  for (int colonne = 0; colonne < TAILLE; colonne++) printf("+---");
  printf("+\n");
}

/** @brief Nomme le vainqueur ou annonce le match nul.
 * @param partie Partie terminée dont le résultat est affiché. */
void afficherResultat(const struct Partie *partie) {
  if (partie->etat == GAGNEE)
    printf("Victoire de %s (%c) !\n", partie->joueurs[partie->gagnant].nom,
           partie->joueurs[partie->gagnant].pion);
  else if (partie->etat == NULLE) printf("Match nul : le plateau est plein.\n");
}
