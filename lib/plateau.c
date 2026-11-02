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
 * @return 1 si le coup est autorisé, 0 sinon. */
int verifierCoup(const struct Partie *partie, struct Coup coup) {
  if (partie->gagnant != -1 || partie->nombreCoups == TAILLE * TAILLE) {
    return 0;
  }
  if (coup.ligne < 1 || coup.ligne > TAILLE ||
      coup.colonne < 1 || coup.colonne > TAILLE) {
    return 0;
  }
  if (partie->grille[coup.ligne - 1][coup.colonne - 1] != VIDE) {
    return 0;
  }
  return 1;
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
 * @return 1 si le coup est accepté, 0 sinon. */
int jouerCoup(struct Partie *partie, struct Coup coup) {
  if (!verifierCoup(partie, coup)) {
    return 0;
  }
  partie->grille[coup.ligne - 1][coup.colonne - 1] =
      partie->joueurs[partie->joueurCourant].pion;
  partie->nombreCoups++;
  partie->gagnant = chercherGagnant(partie);
  if (partie->gagnant == -1 && partie->nombreCoups < TAILLE * TAILLE) {
    partie->joueurCourant = (partie->joueurCourant + 1) % NB_JOUEURS;
  }
  return 1;
}
