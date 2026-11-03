/** @file types.h @brief Constantes et informations échangées entre les modules.
 */
#ifndef MORPION_TYPES_H
#define MORPION_TYPES_H
#define MODE_DEUX_JOUEURS 1
#define MODE_ORDINATEUR 2
#define TAILLE 3        /**< Nombre de lignes et de colonnes. */
#define VIDE ' '        /**< Contenu d'une case libre. */
#define CAPACITE_NOM 64 /**< Capacité du nom, terminateur compris. */
#define NB_JOUEURS 2    /**< Nombre de joueurs humains. */
/** @brief Identité et symbole d'un joueur. */
typedef struct Joueur {
  char nom[CAPACITE_NOM]; /**< Mot de 1 à 63 octets. */
  char pion;              /**< X ou O. */
} Joueur;
/** @brief Coordonnées saisies, numérotées à partir de 1. */
typedef struct Coup {
  int ligne;   /**< Ligne visée. */
  int colonne; /**< Colonne visée. */
} Coup;
/** @brief Ensemble des informations d'une partie. */
typedef struct Partie {
  char grille[TAILLE][TAILLE]; /**< Plateau de jeu. */
  Joueur joueurs[NB_JOUEURS];  /**< Identités conservées lors du rejeu. */
  int joueurCourant;           /**< Indice du joueur qui doit jouer (0 ou 1). */
  int nombreCoups;             /**< Nombre de cases occupées. */
  int gagnant;                 /**< Indice du vainqueur, ou -1 si absent. */
  int mode;                    /* Mode de jeu choisi */
} Partie;
#endif
