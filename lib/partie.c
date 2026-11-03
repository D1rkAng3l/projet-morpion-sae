/** @file partie.c @brief Coordination de la saisie, des règles et de
 * l'affichage. */
#include "partie.h"

#include <stdio.h>

#include "affichage.h"
#include "plateau.h"
#include "saisie.h"

/** @brief Réinitialise puis conduit une partie jusqu'au résultat ou à EOF.
 * @pre partie est accessible en écriture et contient deux noms terminés
 * par le caractère nul. Son plateau et ses compteurs seront réinitialisés.
 * @param partie Partie contenant les noms déjà saisis.
 * @return 1 si terminée normalement, 0 si l'entrée est interrompue. */
int jouerPartie(struct Partie* partie) {
  initialiserPartie(partie);
  afficherPartie(partie);
  while (partie->gagnant == -1 && partie->nombreCoups < TAILLE * TAILLE) {
    /* Vérification du joueur courant */
    if (partie->mode == MODE_ORDINATEUR && partie->joueurCourant == 1) {
      /* Tour de l'ordinateur */
      jouerOrdinateur(partie);
    } else {
      /* Tour d'un joueur humain */
      printf("A %s de jouer (%c). Saisir ligne colonne (1 a %d) : ",
             partie->joueurs[partie->joueurCourant].nom,
             partie->joueurs[partie->joueurCourant].pion, TAILLE);
      struct Coup coup;
      int statut = lireCoup(&coup);
      if (statut == 0) {
        return 0;
      }
      if (statut == -1) {
        fprintf(stderr,
                "Saisie invalide : entrez deux chiffres, par exemple 2 3.\n");
      } else {
        if (jouerCoup(partie, coup)) {
          afficherPartie(partie);
        } else if (coup.ligne < 1 || coup.ligne > TAILLE || coup.colonne < 1 ||
                   coup.colonne > TAILLE) {
          fprintf(stderr,
                  "Case hors du plateau : ligne et colonne doivent etre entre "
                  "1 et %d.\n",
                  TAILLE);
        } else {
          fprintf(stderr, "Case deja occupee : choisissez une case vide.\n");
        }
      }
    }
  }

  afficherResultat(partie);

  return 1;
}

/** @brief Fait jouer l'ordinateur .
 * @param partie Partie en cours.
 */
void jouerOrdinateur(struct Partie* partie) {
  struct Coup coup;

  /* Parcours du plateau */
  for (int ligne = 1; ligne <= TAILLE; ligne++) {
    for (int colonne = 1; colonne <= TAILLE; colonne++) {
      coup.ligne = ligne;
      coup.colonne = colonne;

      /* Vérification de la disponibilité de la case */
      if (verifierCoup(partie, coup)) {
        printf("L'ordinateur joue : ligne %d, colonne %d.\n", ligne, colonne);

        /* L'ordinateur joue son coup */
        jouerCoup(partie, coup);

        afficherPartie(partie);

        return;
      }
    }
  }
}