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
  while (partie->etat == EN_COURS) {
    printf("A %s de jouer (%c). Saisir ligne colonne (1 a %d) : ",
           partie->joueurs[partie->joueurCourant].nom,
           partie->joueurs[partie->joueurCourant].pion, TAILLE);
    struct Coup coup;
    enum LectureCoup statut = lireCoup(&coup);
    if (statut == FIN_SAISIE) {
      return 0;
    }
    if (statut == FORMAT_INVALIDE) {
      fprintf(stderr, "Saisie invalide : entrez deux entiers sans signe, par exemple 2 3.\n");
    } else {
      enum ControleCoup controle = jouerCoup(partie, coup);
      if (controle == HORS_PLATEAU) {
        fprintf(stderr, "Case hors du plateau : ligne et colonne doivent etre entre 1 et %d.\n", TAILLE);
      } else if (controle == CASE_OCCUPEE) {
        fprintf(stderr, "Case deja occupee : choisissez une case vide.\n");
      } else {
        afficherPartie(partie);
      }
    }
  }
  afficherResultat(partie);
  return 1;
}
