/** @file plateau.c @brief Règles indépendantes du clavier et de l'affichage. */
#include "plateau.h"

/** @brief Vide le plateau et remet X au premier tour, sans effacer les noms.
 * @pre partie désigne une structure accessible en écriture.
 * @param partie Partie à réinitialiser. */
void initialiserPartie(struct Partie *partie) {
  partie->joueurs[0].pion = 'X';
  partie->joueurs[1].pion = 'O';
  partie->joueurCourant = 0;
  partie->nombreCoups = 0;
  partie->etat = EN_COURS;
  partie->gagnant = -1;
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      partie->grille[ligne][colonne] = VIDE;
    }
  }
}

/** @brief Contrôle les limites, l'état et l'occupation sans modifier la partie.
 * @pre partie désigne une partie initialisée par initialiserPartie ;
 * les pions des joueurs sont distincts et différents de VIDE.
 * @param partie Partie à consulter. @param coup Case visée.
 * @return Motif du refus ou COUP_VALIDE. */
enum ControleCoup verifierCoup(const struct Partie *partie, struct Coup coup) {
  if (partie->etat != EN_COURS) {
    return PARTIE_TERMINEE;
  }
  if (coup.ligne < 1 || coup.ligne > TAILLE ||
      coup.colonne < 1 || coup.colonne > TAILLE) {
    return HORS_PLATEAU;
  }
  if (partie->grille[coup.ligne - 1][coup.colonne - 1] != VIDE) {
    return CASE_OCCUPEE;
  }
  return COUP_VALIDE;
}

/** @brief Cherche un alignement de trois pions identiques non vides.
 * @pre partie désigne une partie initialisée par initialiserPartie ;
 * les pions des joueurs sont distincts et différents de VIDE.
 * @param partie Partie à consulter. @return Indice du gagnant, ou -1. */
int chercherGagnant(const struct Partie *partie) {
  for (int joueur = 0; joueur < NB_JOUEURS; joueur++) {
    char pion = partie->joueurs[joueur].pion;
    for (int ligne = 0; ligne < TAILLE; ligne++) {
      int alignes = 1;
      for (int colonne = 0; colonne < TAILLE; colonne++) {
        if (partie->grille[ligne][colonne] != pion) {
          alignes = 0;
        }
      }
      if (alignes) {
        return joueur;
      }
    }
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      int alignes = 1;
      for (int ligne = 0; ligne < TAILLE; ligne++) {
        if (partie->grille[ligne][colonne] != pion) {
          alignes = 0;
        }
      }
      if (alignes) {
        return joueur;
      }
    }
    int diagonale = 1;
    int antiDiagonale = 1;
    for (int i = 0; i < TAILLE; i++) {
      if (partie->grille[i][i] != pion) {
        diagonale = 0;
      }
      if (partie->grille[i][TAILLE - 1 - i] != pion) {
        antiDiagonale = 0;
      }
    }
    if (diagonale || antiDiagonale) {
      return joueur;
    }
  }
  return -1;
}

/** @brief Pose un coup valide et actualise le résultat.
 * La main passe seulement après un coup accepté si la partie continue.
 * Un coup refusé ne modifie aucune information.
 * @pre partie désigne une partie initialisée et accessible en écriture.
 * @param partie Partie à modifier. @param coup Case visée.
 * @return Motif du refus ou COUP_VALIDE après placement. */
enum ControleCoup jouerCoup(struct Partie *partie, struct Coup coup) {
  enum ControleCoup controle = verifierCoup(partie, coup);
  if (controle != COUP_VALIDE) {
    return controle;
  }
  partie->grille[coup.ligne - 1][coup.colonne - 1] =
      partie->joueurs[partie->joueurCourant].pion;
  partie->nombreCoups++;
  partie->gagnant = chercherGagnant(partie);
  // Une victoire au neuvième coup doit être annoncée avant un éventuel nul.
  if (partie->gagnant != -1) {
    partie->etat = GAGNEE;
  }
  else if (partie->nombreCoups == TAILLE * TAILLE) {
    partie->etat = NULLE;
  }
  else {
    partie->joueurCourant = (partie->joueurCourant + 1) % NB_JOUEURS;
  }
  return COUP_VALIDE;
}
