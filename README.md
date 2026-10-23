# Morpion — SAÉ 1.01 et 1.02

**Groupe G1E** : Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe et suivi

| Membre            | Mention   | Responsabilité                       |
| ----------------- | --------- | ------------------------------------ |
| Mathis Bretonneau | `@Mathis` | Coordination, configuration et suivi |
| Ilan Guiot        | `@Ilan`   | Conception et algorithmique          |
| Elisa Mayet       | `@ELisa`  | Développement et intégration         |
| Tilio Dabaji      | `@Tilio`  | Essais, documentation et qualité     |

La répartition ci-dessus décrit les responsabilités prévues. Les mentions du journal et les auteurs des contributions doivent être confirmés par les personnes concernées avant le rendu : une responsabilité prévue ne prouve pas une réalisation personnelle.

## Version actuelle : semaine 4

Le morpion se joue à deux sur une grille de 3 × 3. Le premier joueur utilise X, le second O. Les joueurs alternent uniquement après un coup accepté. Trois pions identiques alignés sur une ligne, une colonne ou une diagonale donnent la victoire, annoncée avec le nom du gagnant. Si le plateau est plein sans alignement, le programme annonce un match nul. Une victoire au neuvième coup reste une victoire.

Le résultat arrête la partie immédiatement. Le programme propose de rejouer avec les mêmes joueurs : une nouvelle partie commence sur un plateau vide, compteur à zéro et X au premier tour. Il n’y a pas d’IA, de hasard ou de score cumulé dans cette version.

## Compilation sous Linux

Compiler et lancer depuis la racine :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

## Jouer et arrêter une session

1. Saisir le nom de chacun des deux joueurs, un nom par ligne. Un nom est un mot sans espace de 1 à 63 octets. Les lignes blanches sont ignorées ; si une ligne contient plusieurs mots, seul le premier est conservé. Un nom trop long est refusé et le reste de sa ligne est consommé. Les accents UTF-8 peuvent occuper plusieurs octets.
2. Le joueur appelé saisit la ligne puis la colonne sur une seule ligne : `2 3` vise la ligne 2, colonne 3. Les repères vont de 1 à 3. Espaces, tabulations et retours chariot sont acceptés comme séparateurs internes.
3. Une ligne vide, du texte, un nombre signé ou décimal, une coordonnée manquante ou un élément supplémentaire est refusé. Les cases hors plateau et les cases occupées ont des messages distincts. Le même joueur recommence sans modification du plateau ni du compteur.
4. Après le résultat, répondre `o` pour rejouer ou `n` pour terminer ; les majuscules sont acceptées. Toute autre réponse est refusée. Le rejeu conserve les noms, vide le plateau et redonne le premier tour à X.

Sous Linux, **Ctrl+D** sur une entrée vide signale la fin de saisie. Si la session est incomplète, le programme s’arrête avec un message sur `stderr` et le code 1. Une session terminée par `n` renvoie 0. Une dernière ligne complète sans retour à la ligne est traitée.

`./jeu --aide` affiche le mode d’emploi et renvoie 0. Les autres arguments sont refusés avec le code 1.

## Configuration VS Code du modèle

Le dossier `.vscode/` contient uniquement les quatre fichiers du ZIP fourni, identiques octet par octet : `tasks.json`, `settings.json`, `c_cpp_properties.json` et `extensions.json`. Aucune tâche supplémentaire ni configuration `launch.json` n’est conservée.

Pour **Ctrl+Maj+B**, ouvrir `jeu.c` à la racine comme fichier actif. La tâche originale utilise `${file}` et compile aussi `lib/*.c`. Lancer cette tâche avec un autre onglet actif ne compile pas correctement le projet. Aucune configuration personnalisée de F5 n’est livrée.

## Organisation du projet

| Fichier | Responsabilité |
| --- | --- |
| `jeu.c` | Point d’entrée : arguments, noms et boucle de rejeu |
| `lib/types.h` | Constantes, structures Joueur/Coup/Partie et états partagés |
| `lib/plateau.c/.h` | Initialisation, contrôle des coups, placement, victoire et nul ; aucune entrée-sortie |
| `lib/saisie.c/.h` | Lecture des noms, des coordonnées et de la réponse au rejeu |
| `lib/affichage.c/.h` | Affichage du plateau, du compteur et du résultat |
| `lib/partie.c/.h` | Déroulement d’une partie et coordination des autres modules |
| `Doxyfile` | Configuration de la documentation générée dans `html/` |
| `output/` | Jeux d’essai, sorties réelles, erreurs et bilan des vérifications |
| `rapport/` | Compte rendu HTML : présentation, conception et suivi |

Les fonctions échangent les structures ; les fonctions qui consultent la partie reçoivent un pointeur constant. Les règles peuvent être utilisées sans lire le clavier ni afficher de texte. `lib/partie.c/.h` sont nécessaires à `jouerPartie` et doivent être conservés avec le reste des sources. Le module d’exemple inutilisé a été retiré.

## Contrats et saisie

Les préconditions sont indiquées dans les commentaires de chaque fonction : adresses accessibles, partie initialisée pour les règles, noms terminés par le caractère nul pour le dialogue. Elles décrivent les obligations du programme appelant ; les erreurs de l’utilisateur sont contrôlées séparément et ne provoquent pas d’assertion.

`lireCoordonnee` consomme un entier sans signe et conserve le premier caractère qui suit. Les valeurs supérieures au plateau sont plafonnées à `TAILLE + 1` ; les chiffres suivants sont consommés sans poursuivre le calcul. `lireCoup` assemble deux coordonnées et refuse tout élément supplémentaire, sans franchir la fin de ligne ni laisser ses restes pour le tour suivant.

`enum LectureCoup` distingue `COUP_LU`, `FORMAT_INVALIDE` et `FIN_SAISIE`. `enum ChoixRejeu` distingue `REJOUER`, `ARRETER` et `REJEU_INTERROMPU`. Le format d’un coup est ainsi séparé du contrôle des règles, réalisé par `verifierCoup` et `jouerCoup`.

## Arbre fonctionnel avec signatures

```text
int main(int argc, char *argv[])
├── int demanderNom(struct Joueur *joueur, int numero) [pour chaque joueur]
│   └── int estSeparateur(int caractere)
└── boucle de rejeu
    ├── int jouerPartie(struct Partie *partie)
    │   ├── void initialiserPartie(struct Partie *partie)
    │   ├── void afficherPartie(const struct Partie *partie) [initial puis coups acceptés]
    │   ├── boucle tant que etat == EN_COURS
    │   │   ├── enum LectureCoup lireCoup(struct Coup *coup)
    │   │   │   ├── int lireCoordonnee(int *caractere) [ligne puis colonne]
    │   │   │   │   └── int estSeparateur(int caractere)
    │   │   │   └── int estSeparateur(int caractere) [blancs en fin de ligne]
    │   │   └── enum ControleCoup jouerCoup(struct Partie *partie, struct Coup coup)
    │   │       ├── enum ControleCoup verifierCoup(const struct Partie *partie, struct Coup coup)
    │   │       └── int chercherGagnant(const struct Partie *partie)
    │   └── void afficherResultat(const struct Partie *partie)
    └── enum ChoixRejeu demanderRejouer(void)
        └── int estSeparateur(int caractere)
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
├── html/       (documentation générée)
├── output/     (jeux d’essai et traces)
├── rapport/    (compte rendu HTML)
└── lib/
    ├── types.h
    ├── saisie.c
    ├── saisie.h
    ├── plateau.c
    ├── plateau.h
    ├── affichage.c
    ├── affichage.h
    ├── partie.c
    └── partie.h
```

## Documentation Doxygen

Chaque fonction est documentée avant sa déclaration avec son rôle, ses paramètres et son retour lorsqu’elle en a un. Les définitions reprennent explicitement ces contrats. Les structures, champs et énumérations sont également décrits.

```bash
doxygen Doxyfile
```

Ouvrir ensuite `html/index.html`. Le dossier `html/` est suivi par Git et fait partie de la documentation à remettre ; il doit être régénéré après toute modification des sources ou des documents. Le README est la page d’accueil, le [CHANGELOG](CHANGELOG.md) est aussi intégré. `jeu.c` et tous les fichiers `.c/.h` de `lib/` figurent dans la documentation avec leurs sources. La configuration traite les avertissements comme des erreurs et ne génère pas de PDF/LaTeX.

## Jeux d’essai et flux standard

Le dialogue, les plateaux et les résultats vont sur `stdout`. Les seuls messages sur `stderr` sont les erreurs : saisie invalide, coup refusé, argument invalide ou fin prématurée d’entrée. Une erreur de saisie récupérable ne termine pas le jeu.

Les sept jeux d’essai sont décrits dans [output/README.md](output/README.md). Pour en rejouer un depuis la racine, séparer les deux flux :

```bash
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
```

Remplacer `01` par le numéro souhaité. Les scénarios 01 à 04, 06 et 07 terminent normalement avec le code 0. Le scénario 05 coupe volontairement l’entrée : le programme annonce l’interruption sur `stderr` et renvoie 1 sans redemander indéfiniment un coup. Une même entrée donne les mêmes sorties ; aucun hasard n’est utilisé.

## Compte rendu HTML et suivi

Le compte rendu HTML (`rapport/index.html`) contient la présentation du jeu et des fonctionnalités, la conception en modules, et un tableau des difficultés et solutions avec responsables. Les membres doivent compléter les observations personnelles au fil des séances ; aucune participation passée n’est inventée. Ce compte rendu est distinct de la documentation Doxygen.

[CHANGELOG.md](CHANGELOG.md) suit les modifications par semaine. Aucun script de génération ni workflow n’est ajouté. Les exécutables locaux et les métadonnées de Git ne font pas partie du rendu. Aucun ZIP n’est créé.

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
