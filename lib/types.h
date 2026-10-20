/** @file types.h @brief Constantes et informations échangées entre les modules. */
#ifndef MORPION_TYPES_H
#define MORPION_TYPES_H
#define TAILLE 3 /**< Nombre de lignes et de colonnes. */
#define VIDE ' ' /**< Contenu d'une case libre. */
#define CAPACITE_NOM 64 /**< Capacité du nom, terminateur compris. */
#define NB_JOUEURS 2 /**< Nombre de joueurs humains. */
/** @brief Identité et symbole d'un joueur. */
struct Joueur {
  char nom[CAPACITE_NOM]; /**< Mot de 1 à 63 octets. */
  char pion; /**< X ou O. */
};
/** @brief Coordonnées saisies, numérotées à partir de 1. */
struct Coup {
  int ligne; /**< Ligne visée. */
  int colonne; /**< Colonne visée. */
};
/** @brief État de la partie. */
enum EtatPartie {
  EN_COURS, /**< Des coups restent possibles. */
  GAGNEE, /**< Un joueur a aligné trois pions. */
  NULLE /**< Plateau plein sans vainqueur. */
};
/** @brief Résultat du contrôle d'un coup, sans effet sur la partie. */
enum ControleCoup {
  COUP_VALIDE, /**< La pose est autorisée. */
  HORS_PLATEAU, /**< Coordonnées hors des repères. */
  CASE_OCCUPEE, /**< Un pion est déjà présent. */
  PARTIE_TERMINEE /**< Aucun coup autorisé après le résultat. */
};
/** @brief Ensemble des informations d'une partie. */
struct Partie {
  char grille[TAILLE][TAILLE]; /**< Plateau de jeu. */
  struct Joueur joueurs[NB_JOUEURS]; /**< Identités conservées lors du rejeu. */
  int joueurCourant; /**< Indice du joueur qui doit jouer (0 ou 1). */
  int nombreCoups; /**< Nombre de cases occupées. */
  enum EtatPartie etat; /**< En cours, gagnée ou nulle. */
  int gagnant; /**< Indice du vainqueur, ou -1 si absent. */
};
#endif
