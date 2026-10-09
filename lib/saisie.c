// Lecture bornée des noms des joueurs.
#include "saisie.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int lireLigne(char *texte, size_t capacite) {
  if (capacite < 2 || capacite > INT_MAX) return 0;
  if (!fgets(texte, (int)capacite, stdin)) return 0;
  char *fin = strchr(texte, '\n');
  if (fin) {
    *fin = '\0';
  } else {
    int caractere = getchar();
    if (caractere != '\n' && caractere != EOF) {
      while ((caractere = getchar()) != '\n' && caractere != EOF) {}
      return -1;
    }
  }
  size_t longueur = strlen(texte);
  if (longueur && texte[longueur - 1] == '\r') texte[longueur - 1] = '\0';
  return 1;
}

bool demanderNom(char *nom, size_t capacite, int numero) {
  for (;;) {
    printf("Nom du joueur %d (1 a %zu octets) : ", numero, capacite - 1);
    fflush(stdout);
    int statut = lireLigne(nom, capacite);
    if (!statut) return false;
    if (statut == 1) {
      size_t debut = 0;
      while (isspace((unsigned char)nom[debut])) ++debut;
      size_t fin = strlen(nom);
      while (fin > debut && isspace((unsigned char)nom[fin - 1])) --fin;
      nom[fin] = '\0';
      memmove(nom, nom + debut, fin - debut + 1);
      if (*nom) return true;
    }
    puts("Nom vide ou trop long : recommencez.");
  }
}
