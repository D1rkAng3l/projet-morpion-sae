/** @file jeu.c @brief Point d'entrée : arguments, joueurs et boucle de rejeu.
 */
#include <stdio.h>
#include <string.h>

#include "lib/partie.h"
#include "lib/saisie.h"

/** @brief Lance les parties ou affiche l'aide.
 * @param argc Nombre d'arguments, nom du programme compris.
 * @param argv Arguments ; seule l'option --aide est acceptée.
 * @return 0 après une sortie normale, 1 si les arguments sont invalides ou si
 * l’entrée se termine avant la fin attendue de la session.
 */
int main(int argc, char* argv[]) {
  if (argc == 2 && strcmp(argv[1], "--aide") == 0) {
    printf(
        "Morpion : ./jeu [--aide]\nDeux noms puis un coup ligne colonne par "
        "ligne.\n"
        "Apres le resultat : o pour rejouer, n pour terminer.\n"
        "Rejeu automatique : ./jeu < output/partie-01.in > "
        "output/partie-01.out 2> output/partie-01.err\n");
    return 0;
  }
  if (argc != 1) {
    fprintf(stderr, "Argument invalide. Utilisez ./jeu --aide.\n");
    return 1;
  }
  struct Partie partie;
  for (int joueur = 0; joueur < NB_JOUEURS; joueur++) {
    if (!demanderNom(&partie.joueurs[joueur], joueur + 1)) {
      fprintf(stderr, "Fin de saisie avant les deux noms.\n");
      return 1;
    }
  }
  printf("Joueurs : %s (X) et %s (O).\n", partie.joueurs[0].nom,
         partie.joueurs[1].nom);
  enum ChoixRejeu rejouer;
  do {
    if (!jouerPartie(&partie)) {
      fprintf(stderr, "Fin de saisie : partie interrompue.\n");
      return 1;
    }
    rejouer = demanderRejouer();
    if (rejouer == REJEU_INTERROMPU) {
      fprintf(stderr, "Fin de saisie avant la reponse de rejeu.\n");
      return 1;
    }
  } while (rejouer == REJOUER);
  printf("Fin du jeu.\n");
  return 0;
}
