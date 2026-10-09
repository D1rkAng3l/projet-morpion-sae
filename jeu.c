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
{

    void initialiserGrille(char grille[3][3])
    {

        for (int ligne=0;ligne < 3;ligne++)               //parcours des lignes
        {
            for (int colonne=0;colonne < 3;colonne++)     //parcours des colones de cette ligne
            {
                grille[ligne][colonne] = ' ';             // un espace dans la case
            }
        }
    }
    void afficherGrille(const char grille[3][3])
    {
        printf("      0       1       2\n");              //affichage numero colonne
        printf("    +-------+-------+-------+\n");        //affiche la 1ere ligne

        for (int ligne=0;ligne < 3; ligne++)              //parcours des lignes
        {
            printf(" %d  |",ligne);                       //affiche le numero de la ligne
            for (int colonne=0; colonne < 3; colonne++)   //parcours des colones de la ligne
            {
                printf("   %c   |",grille[ligne][colonne]);//affiche le contenu de la case
            }
            printf("\n    +-------+-------+-------+\n");   //affiche la ligne
        }


    }
return 0;
}