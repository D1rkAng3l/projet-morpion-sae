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
/** @brief Ensemble des informations d'une partie. */
struct Partie {
  char grille[TAILLE][TAILLE]; /**< Plateau de jeu. */
  struct Joueur joueurs[NB_JOUEURS]; /**< Identités conservées lors du rejeu. */
  int joueurCourant; /**< Indice du joueur qui doit jouer (0 ou 1). */
  int nombreCoups; /**< Nombre de cases occupées. */
  int gagnant; /**< Indice du vainqueur, ou -1 si absent. */
};
#endif
