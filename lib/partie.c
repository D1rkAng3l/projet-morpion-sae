/** @file partie.c @brief Coordination de la saisie, des règles et de l'affichage. */
#include "partie.h"
#include "affichage.h"
#include "plateau.h"
#include "saisie.h"
#include <stdio.h>

/** @brief Réinitialise puis conduit une partie jusqu'au résultat ou à EOF.
 * @pre partie est accessible en écriture et contient deux noms terminés
 * par le caractère nul. Son plateau et ses compteurs seront réinitialisés.
 * @param partie Partie contenant les noms déjà saisis.
 * @return 1 si terminée normalement, 0 si l'entrée est interrompue. */
int jouerPartie(struct Partie *partie) {
  initialiserPartie(partie);
  afficherPartie(partie);
  while (partie->gagnant == -1 && partie->nombreCoups < TAILLE * TAILLE) {
    printf("A %s de jouer (%c). Saisir ligne colonne (1 a %d) : ",
           partie->joueurs[partie->joueurCourant].nom,
           partie->joueurs[partie->joueurCourant].pion, TAILLE);
    struct Coup coup;
    int statut = lireCoup(&coup);
    if (statut == 0) {
      return 0;
    }
    if (statut == -1) {
      fprintf(stderr, "Saisie invalide : entrez deux chiffres, par exemple 2 3.\n");
    } else {
      if (jouerCoup(partie, coup)) {
        afficherPartie(partie);
      } else if (coup.ligne < 1 || coup.ligne > TAILLE ||
                 coup.colonne < 1 || coup.colonne > TAILLE) {
        fprintf(stderr, "Case hors du plateau : ligne et colonne doivent etre entre 1 et %d.\n", TAILLE);
      } else {
        fprintf(stderr, "Case deja occupee : choisissez une case vide.\n");
      }
    }
  }
  afficherResultat(partie);
  return 1;
}
