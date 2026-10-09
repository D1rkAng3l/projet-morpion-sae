// Saisie des noms et lecture bornée.
#ifndef MORPION_SAISIE_H
#define MORPION_SAISIE_H
#include <stdbool.h>
#include <stddef.h>
#define CAPACITE_NOM 64

int lireLigne(char *texte, size_t capacite);
bool demanderNom(char *nom, size_t capacite, int numero);
#endif
