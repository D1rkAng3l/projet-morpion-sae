/** @file saisie.c @brief Saisies bornées avec les entrées-sorties du cours. */
#include "saisie.h"
#include <stdio.h>

/** @brief Reconnaît les blancs acceptés à l'intérieur d'une ligne.
 * @param caractere Caractère lu avec getchar, ou EOF.
 * @return 1 pour espace, tabulation ou retour chariot, 0 sinon.
 * Le saut de ligne termine la saisie et n'est pas un séparateur interne. */
int estSeparateur(int caractere) {
  return caractere == ' ' || caractere == '\t' || caractere == '\r';
}

/** @brief Lit un entier sans signe à partir d'un caractère déjà disponible.
 * Saute les séparateurs internes et plafonne la valeur à TAILLE + 1.
 * @pre caractere désigne un entier accessible contenant le caractère courant.
 * @param caractere Adresse du caractère courant ; reçoit le premier caractère
 * non numérique après la coordonnée, ou la fin de ligne/EOF.
 * @return Valeur plafonnée, ou -1 si aucun chiffre n'a été lu.
 * La fonction ne franchit pas la fin de ligne. */
int lireCoordonnee(int *caractere) {
  while (estSeparateur(*caractere)) {
    *caractere = getchar();
  }
  if (*caractere < '0' || *caractere > '9') {
    return -1;
  }
  int valeur = 0;
  while (*caractere >= '0' && *caractere <= '9') {
    // Après dépassement, lire les chiffres restants sans continuer le calcul.
    if (valeur <= TAILLE) {
      valeur = valeur * 10 + *caractere - '0';
      if (valeur > TAILLE) {
        valeur = TAILLE + 1;
      }
    }
    *caractere = getchar();
  }
  return valeur;
}

/** @brief Demande un mot de 1 à 63 octets et consomme le reste de sa ligne.
 * @pre joueur désigne un joueur accessible en écriture ; numero vaut 1 ou 2.
 * @param joueur Joueur dont le nom est rempli.
 * @param numero Numéro affiché.
 * @return 1 si le nom est accepté, 0 à EOF. */
int demanderNom(struct Joueur *joueur, int numero) {
  int tropLong;
  do {
    printf("Nom du joueur %d (1 a 63 octets, sans espace) : ", numero);
    if (scanf("%63s", joueur->nom) != 1) {
      return 0;
    }
    int caractere = getchar();
    tropLong = caractere != '\n' && !estSeparateur(caractere) && caractere != EOF;
    while (caractere != '\n' && caractere != EOF) {
      caractere = getchar();
    }
    if (tropLong) {
      fprintf(stderr, "Nom trop long : recommencez.\n");
    }
  } while (tropLong);
  return 1;
}

/** @brief Lit deux entiers sans signe, séparés par des blancs, sur une ligne.
 * Les valeurs trop grandes sont plafonnées à TAILLE + 1, sans débordement.
 * @pre coup désigne une structure accessible en écriture.
 * @param coup Coordonnées remplies seulement si le format est correct.
 * @return COUP_LU si correct, FORMAT_INVALIDE sinon, FIN_SAISIE à EOF avant
 * la ligne. Toute la ligne est consommée, même après une erreur. */
enum LectureCoup lireCoup(struct Coup *coup) {
  int caractere = getchar();
  if (caractere == EOF) {
    return FIN_SAISIE;
  }
  struct Coup lu;
  lu.ligne = lireCoordonnee(&caractere);
  lu.colonne = lireCoordonnee(&caractere);
  while (estSeparateur(caractere)) {
    caractere = getchar();
  }
  int correct = lu.ligne >= 0 && lu.colonne >= 0 &&
                (caractere == '\n' || caractere == EOF);
  // Consommer les éléments supplémentaires pour repartir sur la ligne suivante.
  while (caractere != '\n' && caractere != EOF) {
    caractere = getchar();
  }
  if (!correct) {
    return FORMAT_INVALIDE;
  }
  *coup = lu;
  return COUP_LU;
}

/** @brief Demande o/n ; recommence après une réponse invalide.
 * @return REJOUER pour oui, ARRETER pour non, REJEU_INTERROMPU à EOF. */
enum ChoixRejeu demanderRejouer(void) {
  while (1) {
    printf("Rejouer avec les memes joueurs ? (o/n) : ");
    int reponse = 0;
    int invalide = 0;
    int caractere = getchar();
    if (caractere == EOF) {
      return REJEU_INTERROMPU;
    }
    while (caractere != '\n' && caractere != EOF) {
      if (!estSeparateur(caractere)) {
        if (reponse == 0) {
          reponse = caractere;
        } else {
          invalide = 1;
        }
      }
      caractere = getchar();
    }
    if (!invalide && (reponse == 'o' || reponse == 'O')) {
      return REJOUER;
    }
    if (!invalide && (reponse == 'n' || reponse == 'N')) {
      return ARRETER;
    }
    fprintf(stderr, "Reponse invalide : entrez o ou n.\n");
  }
}
