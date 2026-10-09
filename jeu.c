// Morpion : démonstration des fonctionnalités de la semaine 2.
#include "lib/grille.h"
#include "lib/saisie.h"
#include <stdio.h>

int main(void) {
  char noms[2][CAPACITE_NOM];
  Grille grille;
  if (!demanderNom(noms[0], sizeof noms[0], 1) ||
      !demanderNom(noms[1], sizeof noms[1], 2)) {
    puts("Fin de saisie.");
    return 0;
  }
  initialiserGrille(grille);
  printf("Joueurs : %s (X) et %s (O).\n", noms[0], noms[1]);
  puts("Plateau initial :");
  afficherGrille(grille);
  // Pions placés directement dans le code pour vérifier l'affichage.
  grille[0][0] = 'X';
  grille[TAILLE - 1][TAILLE - 1] = 'O';
  puts("Demonstration : deux pions places dans le code.");
  afficherGrille(grille);
  printf("A %s de jouer (X).\n", noms[0]);
  puts("La saisie des coups sera ajoutee lors d'une prochaine etape.");
  return 0;
}
