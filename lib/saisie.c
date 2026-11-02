/** @file saisie.c @brief Lecture avec scanf et nettoyage de la fin de ligne. */
#include "saisie.h"
#include <stdio.h>

/** @brief Consomme la fin de ligne et vérifie qu'elle ne contient que des blancs.
 * @return 1 si seuls des espaces, tabulations ou retours chariot restent, 0 sinon. */
int terminerLigne(void) {
  int correct = 1;
  int caractere = getchar();
  while (caractere != '\n' && caractere != EOF) {
    if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
      correct = 0;
    }
    caractere = getchar();
  }
  return correct;
}

/** @brief Demande un nom sans espace, limité à 63 octets.
 * @pre joueur est accessible en écriture.
 * @param joueur Joueur dont le nom est rempli.
 * @param numero Numéro affiché.
 * @return 1 si le nom est lu, 0 si l'entrée est épuisée. */
int demanderNom(struct Joueur *joueur, int numero) {
  while (1) {
    printf("Nom du joueur %d (1 a 63 octets, sans espace) : ", numero);
    if (scanf("%63s", joueur->nom) != 1) {
      return 0;
    }
    if (terminerLigne()) {
      return 1;
    }
    fprintf(stderr, "Nom trop long ou contenant plusieurs mots : recommencez.\n");
  }
}

/** @brief Lit deux coordonnées à un chiffre avec scanf.
 * @pre coup est accessible en écriture.
 * @param coup Coordonnées lues, à contrôler avant de jouer.
 * @return 1 si deux chiffres sont lus sans texte supplémentaire, -1 si le
 * format est incorrect, 0 si aucune coordonnée n'est disponible à la fin de l'entrée.
 * Les blancs sont ignorés par scanf ; les valeurs restent à vérifier. */
int lireCoup(struct Coup *coup) {
  int nombreLu = scanf("%1d %1d", &coup->ligne, &coup->colonne);
  if (nombreLu == EOF) {
    return 0;
  }
  int finCorrecte = terminerLigne();
  if (nombreLu != 2 || !finCorrecte) {
    return -1;
  }
  return 1;
}

/** @brief Demande o/n et recommence après une réponse incorrecte.
 * @return 1 pour rejouer, 0 pour arrêter, -1 si l'entrée est épuisée. */
int demanderRejouer(void) {
  char reponse;
  while (1) {
    printf("Rejouer avec les memes joueurs ? (o/n) : ");
    if (scanf(" %c", &reponse) != 1) {
      return -1;
    }
    int finCorrecte = terminerLigne();
    if (finCorrecte && (reponse == 'o' || reponse == 'O')) {
      return 1;
    }
    if (finCorrecte && (reponse == 'n' || reponse == 'N')) {
      return 0;
    }
    fprintf(stderr, "Reponse invalide : entrez o ou n.\n");
  }
}
