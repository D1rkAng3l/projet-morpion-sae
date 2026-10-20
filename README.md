# Morpion — SAÉ 1.01 et 1.02

**Groupe G1E** : Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe et suivi

| Membre            | Mention   | Responsabilité                       |
| ----------------- | --------- | ------------------------------------ |
| Mathis Bretonneau | `@Mathis` | Coordination, configuration et suivi |
| Ilan Guiot        | `@Ilan`   | Conception et algorithmique          |
| Elisa Mayet       | `@ELisa`  | Développement et intégration         |
| Tilio Dabaji      | `@Tilio`  | Essais, documentation et qualité     |

Les mentions du journal désignent les responsables selon cette répartition ; chaque membre doit relire et valider ses contributions. Elles ne prouvent pas, seules, une participation individuelle.

## Version actuelle : semaine 4

Le morpion se joue à deux sur une grille de 3 × 3. Le premier joueur utilise X, le second O. Les joueurs alternent uniquement après un coup accepté. Trois pions identiques alignés sur une ligne, une colonne ou une diagonale donnent la victoire, annoncée avec le nom du gagnant. Si le plateau est plein sans alignement, le programme annonce un match nul. Une victoire au neuvième coup reste une victoire.

Le résultat arrête la partie immédiatement. Le programme propose de rejouer avec les mêmes joueurs : une nouvelle partie commence sur un plateau vide, compteur à zéro et X au premier tour. Il n’y a pas d’IA, de hasard ou de score cumulé dans cette version.

## Compilation sous Linux

Compiler et lancer depuis la racine :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

## Arbre fonctionnel avec signatures

```text
int main(int argc, char *argv[])
├── int demanderNom(struct Joueur *joueur, int numero) [pour chaque joueur]
└── boucle de rejeu
    ├── int jouerPartie(struct Partie *partie)
    │   ├── void initialiserPartie(struct Partie *partie)
    │   ├── void afficherPartie(const struct Partie *partie) [initial puis coups acceptés]
    │   ├── boucle tant que etat == EN_COURS
    │   │   ├── int lireCoup(struct Coup *coup)
    │   │   └── enum ControleCoup jouerCoup(struct Partie *partie, struct Coup coup)
    │   │       ├── enum ControleCoup verifierCoup(const struct Partie *partie, struct Coup coup)
    │   │       └── int chercherGagnant(const struct Partie *partie)
    │   └── void afficherResultat(const struct Partie *partie)
    └── int demanderRejouer(void)
```

## Arbre des dossiers

```projet/
├── jeu.c
├── README.md
├── CHANGELOG.md
├── LICENCE
├── LICENCE-CONTENT
├── .clang-format
├── .gitignore
├── .vscode/
├── Doxyfile
└── lib/
    ├── exemple.c
    ├── exemple.h
    ├── saisie.c
    ├── saisie.h
    ├── plateau.c
    ├── plateau.h
    ├── affichage.c
    ├── affichage.h
    ├── fonctions.c
    └── fonctions.h
```

## Documentation Doxygen

Chaque fonction est documentée avant sa déclaration avec son rôle, ses paramètres et son retour lorsqu’elle en a un. Les définitions reprennent explicitement ces contrats. Les structures, champs et énumérations sont également décrits.

```bash
doxygen Doxyfile
```

Ouvrir ensuite `html/index.html`. Le README est la page d’accueil, le [CHANGELOG](CHANGELOG.md) est aussi intégré. `jeu.c` et tous les fichiers `.c/.h` de `lib/` figurent dans la documentation avec leurs sources. La configuration traite les avertissements comme des erreurs et ne génère pas de PDF/LaTeX.

## Jeux d’essai et flux standard

Le dialogue, les plateaux et les résultats vont sur `stdout`. Les seuls messages sur `stderr` sont les erreurs : saisie invalide, coup refusé, argument invalide ou fin prématurée d’entrée. Une erreur de saisie récupérable ne termine pas le jeu.

## Compte rendu HTML et suivi

Le compte rendu HTML (`rapport/index.html`) contient la présentation du jeu et des fonctionnalités, la conception en modules, et un tableau des difficultés et solutions avec responsables. Les membres doivent compléter les observations personnelles au fil des séances ; aucune participation passée n’est inventée. Ce compte rendu est distinct de la documentation Doxygen.

[CHANGELOG.md](CHANGELOG.md) suit les modifications par semaine. Aucun script de génération ni workflow n’est ajouté. Les exécutables locaux et les métadonnées de Git ne font pas partie du rendu. Aucun ZIP n’est créé.

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
