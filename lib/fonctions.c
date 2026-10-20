#include <stdio.h>

declarationDesJoueurs(joueur) {}

for (int joueur = 0; joueur < NB_JOUEURS; joueur++) {
  do {
    printf("Nom du joueur %d (1 a 63 octets, sans espace) : ", joueur + 1);
    if (scanf("%63s", partie.joueurs[joueur].nom) != 1) {
      printf("Fin de saisie.\n");
      return 0;
    }
    caractere = getchar();
    tropLong = caractere != '\n' && caractere != ' ' && caractere != '\t' &&
               caractere != '\r' && caractere != EOF;
    while (caractere != '\n' && caractere != EOF) {
      caractere = getchar();
    }
    if (tropLong) {
      printf("Nom trop long : recommencez.\n");
    }
  } while (tropLong);
}
printf("Joueurs : %s (X) et %s (O).\n", partie.joueurs[0].nom,
       partie.joueurs[1].nom);

bouclePrincipale() {}
