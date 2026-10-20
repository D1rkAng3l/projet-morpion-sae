/** @file saisie.c @brief Saisies bornées avec les entrées-sorties du cours. */
#include "saisie.h"
#include <stdio.h>

/** @brief Demande un mot de 1 à 63 octets et consomme le reste de sa ligne.
 * @param joueur Joueur dont le nom est rempli. @param numero Numéro affiché.
 * @return 1 si le nom est accepté, 0 à EOF. */
int demanderNom(struct Joueur *joueur, int numero) {
  int tropLong;
  do {
    printf("Nom du joueur %d (1 a 63 octets, sans espace) : ", numero);
    if (scanf("%63s", joueur->nom) != 1) return 0;
    int caractere = getchar();
    tropLong = caractere != '\n' && caractere != ' ' &&
               caractere != '\t' && caractere != '\r' && caractere != EOF;
    while (caractere != '\n' && caractere != EOF) caractere = getchar();
    if (tropLong) fprintf(stderr, "Nom trop long : recommencez.\n");
  } while (tropLong);
  return 1;
}

/** @brief Lit deux entiers sans signe, séparés par des blancs, sur une ligne.
 * Les valeurs trop grandes sont plafonnées à TAILLE + 1, sans débordement.
 * @param coup Coordonnées remplies seulement si le format est correct.
 * @return 1 si correct, -1 si format invalide, 0 à EOF avant la ligne. */
int lireCoup(struct Coup *coup) {
  int valeurs[2] = {0, 0};
  int nombre = 0;
  int dansNombre = 0;
  int invalide = 0;
  int caractere = getchar();
  if (caractere == EOF) return 0;
  while (caractere != '\n' && caractere != EOF) {
    if (caractere >= '0' && caractere <= '9') {
      if (!dansNombre) {
        if (nombre < 3) nombre++;
        dansNombre = 1;
      }
      if (nombre <= 2) {
        if (valeurs[nombre - 1] <= TAILLE) {
          valeurs[nombre - 1] = valeurs[nombre - 1] * 10 + caractere - '0';
          if (valeurs[nombre - 1] > TAILLE) valeurs[nombre - 1] = TAILLE + 1;
        }
      } else invalide = 1;
    } else if (caractere == ' ' || caractere == '\t' || caractere == '\r') {
      dansNombre = 0;
    } else invalide = 1;
    caractere = getchar();
  }
  if (invalide || nombre != 2) return -1;
  coup->ligne = valeurs[0];
  coup->colonne = valeurs[1];
  return 1;
}

/** @brief Demande o/n ; recommence après une réponse invalide.
 * @return 1 pour rejouer, 0 pour terminer, -1 à EOF. */
int demanderRejouer(void) {
  while (1) {
    printf("Rejouer avec les memes joueurs ? (o/n) : ");
    int reponse = 0;
    int invalide = 0;
    int caractere = getchar();
    if (caractere == EOF) return -1;
    while (caractere != '\n' && caractere != EOF) {
      if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
        if (reponse == 0) reponse = caractere;
        else invalide = 1;
      }
      caractere = getchar();
    }
    if (!invalide && (reponse == 'o' || reponse == 'O')) return 1;
    if (!invalide && (reponse == 'n' || reponse == 'N')) return 0;
    fprintf(stderr, "Reponse invalide : entrez o ou n.\n");
  }
}
