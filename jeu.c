/**
 * @file jeu.c
 * @brief Point d'entrée du jeu : démonstration de l'utilisation d'un module
 * du dossier lib/.
 */
#include <stdio.h>

#include "./lib/exemple.h"

void initialiserGrille(char grille[3][3]);
void afficherGrille(const char grille[3][3]);
void jouerPartie(char grille[3][3]);
int demanderCoup(const char grille[3][3], char joueur);
bool coupValide(const char grille[3][3], int position);
void placerCoup(char grille[3][3], int position, char joueur);
bool verifierVictoire(const char grille[3][3], char joueur);
bool grillePleine(const char grille[3][3]);
char changerJoueur(char joueur);
void afficherResultat(char resultat);
int main()

    // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
    afficheSep();

printf("Hello world with separators!\n");

afficheSep();

return 0;
}