// Représentation et affichage du plateau.
#ifndef MORPION_GRILLE_H
#define MORPION_GRILLE_H
#define TAILLE 3
#define VIDE ' '
typedef char Grille[TAILLE][TAILLE];

void initialiserGrille(Grille grille);
void afficherGrille(const Grille grille);
#endif
