// Morpion, semaine 3 : chapitres 1 à 7 du cours R1.01.
// Toutes les instructions du jeu restent dans main.
#include <stdio.h>

#include "./lib/exemple.c"

#define TAILLE 3
#define VIDE ' '
#define CAPACITE_NOM 64
#define NB_JOUEURS 2

int main() {
  // ensemble de fonction regroupé avec des typedef
  struct Joueur {
    char nom[CAPACITE_NOM];
    char pion;
  };
  struct Coup {
    int ligne;
    int colonne;
  };
  struct Partie {
    char grille[TAILLE][TAILLE];
    struct Joueur joueurs[NB_JOUEURS];
    int joueurCourant;
    int nombreCoups;
  };

  struct Partie partie;
  struct Coup coup;
  int caractere;
  int tropLong;

  partie.joueurs[0].pion = 'X';
  partie.joueurs[1].pion = 'O';
  partie.joueurCourant = 0;
  partie.nombreCoups = 0;
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      partie.grille[ligne][colonne] = VIDE;
    }
  }

  // scanf borné, une place réservée au caractère EOF '\0'.
  for (int joueur = 0; joueur < NB_JOUEURS; joueur++) {
    do {
      printf("Nom du joueur %d (1 a 63 octets, sans espace) : ", joueur + 1);
      if (scanf("%63s", partie.joueurs[joueur].nom) != 1) {
        printf("Fin de saisie.\n");
        return 0;
      }
      caractere = getchar();
      tropLong = caractere != '\n' && caractere != ' ' && caractere != '\t' &&
                 caractere != '\r' && caractere != EOF;
      while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
      }
      if (tropLong) {
        printf("Nom trop long : recommencez.\n");
      }
    } while (tropLong);
  }
  printf("Joueurs : %s (X) et %s (O).\n", partie.joueurs[0].nom,
         partie.joueurs[1].nom);

  // Afficher l'état initial, puis chaque état après un coup accepté.
  // Boucle principale
  while (1) {
    printf("\nCoups poses : %d\n    ", partie.nombreCoups);
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      printf(" %2d ", colonne + 1);
    }
    printf("\n");
    for (int ligne = 0; ligne < TAILLE; ligne++) {
      printf("    ");
      for (int colonne = 0; colonne < TAILLE; colonne++) {
        printf("+---");
      }
      printf("+\n%3d ", ligne + 1);
      for (int colonne = 0; colonne < TAILLE; colonne++) {
        printf("| %c ", partie.grille[ligne][colonne]);
      }
      printf("|\n");
    }
    printf("    ");
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      printf("+---");
    }
    printf("+\n");

    if (partie.nombreCoups == TAILLE * TAILLE) {
      printf("Plateau plein : aucun coup possible. Fin de la partie.\n");
      break;
    }

    // Vérifier si le coup est valide ou non
    int coupValide = 0;
    do {
      printf("A %s de jouer (%c). Saisir ligne colonne (1 a %d) : ",
             partie.joueurs[partie.joueurCourant].nom,
             partie.joueurs[partie.joueurCourant].pion, TAILLE);

      // Lire la ligne avec getchar, sans conversion avancée.
      // Seuls deux entiers sans signe séparés par des espaces sont acceptés.
      int valeurs[2] = {0, 0};
      int nombre = 0;
      int dansNombre = 0;
      int formatInvalide = 0;
      caractere = getchar();
      if (caractere == EOF) {
        printf("Fin de saisie : partie interrompue.\n");
        return 0;
      }
      while (caractere != '\n' && caractere != EOF) {
        if (caractere >= '0' && caractere <= '9') {
          if (!dansNombre) {
            if (nombre < 3) {
              nombre++;
            }
            dansNombre = 1;
          }
          if (nombre <= 2) {
            // Au-delà de TAILLE, conserver une valeur hors plateau.
            // Cela évite un débordement même avec des milliers de chiffres.
            if (valeurs[nombre - 1] <= TAILLE) {
              valeurs[nombre - 1] = valeurs[nombre - 1] * 10 + caractere - '0';
              if (valeurs[nombre - 1] > TAILLE) {
                valeurs[nombre - 1] = TAILLE + 1;
              }
            }
          } else {
            formatInvalide = 1;
          }
        } else if (caractere == ' ' || caractere == '\t' || caractere == '\r') {
          dansNombre = 0;
        } else {
          formatInvalide = 1;
        }
        caractere = getchar();
      }

      if (formatInvalide || nombre != 2) {
        printf(
            "Saisie invalide : entrez deux entiers sans signe, par exemple 2 "
            "3.\n");
      } else {
        coup.ligne = valeurs[0];
        coup.colonne = valeurs[1];
        if (coup.ligne < 1 || coup.ligne > TAILLE || coup.colonne < 1 ||
            coup.colonne > TAILLE) {
          printf(
              "Case hors du plateau : ligne et colonne doivent etre entre 1 et "
              "%d.\n",
              TAILLE);
        } else if (partie.grille[coup.ligne - 1][coup.colonne - 1] != VIDE) {
          printf("Case deja occupee : choisissez une case vide.\n");
        } else {
          coupValide = 1;
        }
      }
    } while (!coupValide);
    // Tant Que le coup n'est pas valide, vérification jusqu'à ce qu'il le soit
    partie.grille[coup.ligne - 1][coup.colonne - 1] =
        partie.joueurs[partie.joueurCourant].pion;
    partie.nombreCoups++;
    partie.joueurCourant = (partie.joueurCourant + 1) % NB_JOUEURS;
  }
  return 0;
}
