# Morpion — SAÉ 1.01 et 1.02

**Groupe G1E** : Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

| Membre | Mention | Rôle |
| --- | --- | --- |
| Mathis Bretonneau | `@Mathis` | Coordination et suivi |
| Ilan Guiot | `@Ilan` | Conception et algorithmique |
| Elisa Mayet | `@ELisa` | Développement et intégration |
| Tilio Dabaji | `@Tilio` | Essais et documentation |

## Compiler et jouer sous Linux

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

Dans VS Code, ouvrir `jeu.c` puis utiliser **Ctrl+Maj+B**. Les quatre fichiers `.vscode/` sont ceux du modèle fourni.

Saisir un nom sans espace par joueur, de 1 à 63 octets. X commence. Pour jouer, saisir deux coordonnées à un chiffre, par exemple `2 3` pour ligne 2, colonne 3. Les repères vont de 1 à 3. `scanf` ignore les blancs, y compris les lignes vides. La largeur de lecture est limitée à un chiffre par coordonnée. Du texte ou un chiffre supplémentaire après la paire est refusé ; une ligne incorrecte est consommée avant une nouvelle demande.

Un coup hors plateau ou sur une case occupée est refusé sans perdre le tour. Trois pions alignés sur une ligne, une colonne ou une diagonale donnent la victoire. Un plateau plein sans gagnant donne un nul. Une victoire au neuvième coup reste une victoire.

Après le résultat, répondre `o` pour rejouer avec les mêmes noms sur une grille vide, ou `n` pour terminer. Les majuscules sont acceptées. `./jeu --aide` affiche l’aide. Une entrée interrompue, notamment avec Ctrl+D sous Linux, est signalée sur `stderr` avec le code 1 ; une session terminée normalement renvoie 0.

## Organisation du projet

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | Point d’entrée, noms et rejeu |
| `lib/types.h` | Joueur, coup et partie : plateau, joueurs, tour, compteur et gagnant |
| `lib/plateau.c/.h` | Initialisation, validation des coups, placement et victoire, sans entrée-sortie |
| `lib/saisie.c/.h` | Lecture avec `scanf` et nettoyage de la fin de ligne |
| `lib/affichage.c/.h` | Plateau et résultat sur `stdout` |
| `lib/partie.c/.h` | Déroulement d’une partie |
| `output/` | Sept entrées d’essai, sorties et erreurs enregistrées |
| `rapport/` | Compte rendu HTML, conception et suivi des contributions |
| `Doxyfile`, `html/` | Configuration du modèle et documentation générée |

Les fonctions échangent les structures. Un coup refusé ne change pas la partie. L’indice du gagnant vaut -1 tant qu’aucun joueur n’a gagné ; le compteur indique si le plateau est plein. Aucun état supplémentaire ni énumération de résultat n’est nécessaire.

## Schéma fonctionnel

```text
int main(int argc, char *argv[])
├── int demanderNom(struct Joueur *joueur, int numero)
│   └── int terminerLigne(void)
└── boucle de rejeu
    ├── int jouerPartie(struct Partie *partie)
    │   ├── void initialiserPartie(struct Partie *partie)
    │   ├── void afficherPartie(const struct Partie *partie)
    │   ├── boucle tant qu’il reste une case et aucun gagnant
    │   │   ├── int lireCoup(struct Coup *coup)
    │   │   │   └── int terminerLigne(void)
    │   │   └── int jouerCoup(struct Partie *partie, struct Coup coup)
    │   │       ├── int verifierCoup(const struct Partie *partie, struct Coup coup)
    │   │       └── int chercherGagnant(const struct Partie *partie)
    │   └── void afficherResultat(const struct Partie *partie)
    └── int demanderRejouer(void)
        └── int terminerLigne(void)
```

## Essais et documentation

```bash
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
doxygen Doxyfile
```

Remplacer `01` par `02` à `07` pour les autres essais. Le scénario 05 renvoie 1 car son entrée est volontairement interrompue ; les autres renvoient 0. Le dialogue et le résultat vont sur `stdout`. Les messages « hors du plateau », « case occupée », « saisie invalide » et les autres erreurs vont sur `stderr`. Les scénarios sont détaillés dans [output/README.md](output/README.md).

Ouvrir `html/index.html` pour la documentation des fonctions et procédures. Le Doxyfile fourni est conservé, avec ses commentaires et ses options ; seules cinq lignes de réglage sont adaptées au projet. Le README et le [CHANGELOG](CHANGELOG.md) figurent dans la documentation. Le compte rendu (`rapport/index.html`) suit les travaux du groupe, confirmés le 23 octobre 2026.

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
