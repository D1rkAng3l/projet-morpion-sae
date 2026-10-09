// Initialisation et affichage console du plateau.
#include "grille.h"
#include <stdio.h>

void initialiserGrille(Grille grille) {
  for (int ligne = 0; ligne < TAILLE; ++ligne)
    for (int colonne = 0; colonne < TAILLE; ++colonne)
      grille[ligne][colonne] = VIDE;
}

void afficherGrille(const Grille grille) {
  printf("    ");
  for (int colonne = 0; colonne < TAILLE; ++colonne) printf(" %2d ", colonne + 1);
  putchar('\n');
  for (int ligne = 0; ligne < TAILLE; ++ligne) {
    printf("    ");
    for (int colonne = 0; colonne < TAILLE; ++colonne) printf("+---");
    puts("+");
    printf("%3d ", ligne + 1);
    for (int colonne = 0; colonne < TAILLE; ++colonne) printf("| %c ", grille[ligne][colonne]);
    puts("|");
  }
  printf("    ");
  for (int colonne = 0; colonne < TAILLE; ++colonne) printf("+---");
  puts("+");
}
