# Morpion — SAÉ 1.01 et 1.02

**Groupe G1E** : Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe et suivi

| Membre | Mention | Responsabilité |
| --- | --- | --- |
| Mathis Bretonneau | `@Mathis` | Coordination, configuration et suivi |
| Ilan Guiot | `@Ilan` | Conception et algorithmique |
| Elisa Mayet | `@ELisa` | Développement et intégration |
| Tilio Dabaji | `@Tilio` | Essais, documentation et qualité |

Les mentions du journal désignent les responsables selon cette répartition ; chaque membre doit relire et valider ses contributions. Elles ne prouvent pas, seules, une participation individuelle.

## Version actuelle : semaine 4

Le morpion se joue à deux sur une grille de 3 × 3. Le premier joueur utilise X, le second O. Les joueurs alternent uniquement après un coup accepté. Trois pions identiques alignés sur une ligne, une colonne ou une diagonale donnent la victoire, annoncée avec le nom du gagnant. Si le plateau est plein sans alignement, le programme annonce un match nul. Une victoire au neuvième coup reste une victoire.

Le résultat arrête la partie immédiatement. Le programme propose de rejouer avec les mêmes joueurs : une nouvelle partie commence sur un plateau vide, compteur à zéro et X au premier tour. Il n’y a pas d’IA, de hasard ou de score cumulé dans cette version.

## Cours de référence et corrections de l’évaluation

La seule référence de programmation est le [cours R1.01](https://but.lyceum.fr/r101/), relu jusqu’au chapitre 8 :

| Chapitre | Notions appliquées |
| --- | --- |
| [1 — Bases et entrées-sorties](https://but.lyceum.fr/r101/c01/) | Types simples, calculs, `printf`, `scanf`, `getchar` |
| [2 — Contrôle et logique](https://but.lyceum.fr/r101/c02/) | Conditions, boucles, expressions booléennes |
| [3 — Fonctions](https://but.lyceum.fr/r101/c03/) | Prototypes, paramètres, retours, décomposition et documentation |
| [4 — Pointeurs](https://but.lyceum.fr/r101/c04/) | Adresse des structures modifiées et pointeurs constants pour la consultation |
| [5 — Tableaux](https://but.lyceum.fr/r101/c05/) | Matrice, indices et parcours |
| [6 — Chaînes](https://but.lyceum.fr/r101/c06/) | Noms bornés avec `%63s`, comparaison d’argument avec `strcmp` |
| [7 — Structures et types composés](https://but.lyceum.fr/r101/c07/) | Joueur, coup, partie et énumérations d’état |
| [8 — Flux, arguments, modules et documentation](https://but.lyceum.fr/r101/c08/) | `.h/.c`, `argc/argv`, `stderr`, redirections, code de retour et Doxygen |

Le regroupement de tout le code dans `main` est abandonné conformément à la consigne de semaine 4 et au retour du professeur. `jeu.c` contient seulement le point d’entrée. Les règles, l’affichage et la saisie sont séparés ; les fonctions échangent les structures. Aucun fichier `.c` n’est inclus directement. Les paramètres VS Code sont restaurés à l’identique depuis le ZIP fourni, notamment la compilation `lib/*.c`. L’entrée du journal de semaine 3 est datée du 16/10/26 comme demandé dans le retour d’évaluation.

Aucune notion des chapitres ultérieurs n’est requise : pas d’allocation dynamique, de `fgets`, de fonctions avancées de chaînes, de fichiers ouverts par le programme ou d’automatisation Python. Les fichiers d’essai sont lus grâce à la redirection du shell.

## Compilation et utilisation sous Linux

GCC avec C23 et Doxygen pour la documentation sont nécessaires. Compiler et lancer depuis la racine :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

Vérification plus stricte, facultative :

<<<<<<< HEAD
## Utilisation et saisies

1. Saisir les noms des deux joueurs, un nom par ligne. Le premier reçoit X, le second O.
2. Observer le plateau vide, avec lignes et colonnes numérotées de 1 à 3.
3. Le joueur appelé saisit deux entiers sans signe sur une ligne : `2 3` vise la ligne 2, colonne 3.
4. Une saisie refusée affiche une explication ; le même joueur recommence.
5. Après chaque coup accepté, le plateau et le nombre de coups sont affichés. Après neuf coups, la partie termine.

Un nom est un mot de 1 à 63 octets, conservé dans un tableau de 64 octets. Une ligne vide est ignorée pour les noms ; seul le premier mot d’une ligne est conservé. Un mot trop long est refusé, et sa fin de ligne est consommée avant de recommencer.Il est recommandé de ne pas utiliser d'accents.

Pour les coups, les lignes vides, le texte, les nombres signés ou décimaux, les coordonnées manquantes et les éléments supplémentaires sont refusés. Les valeurs 0 ou supérieures à 3 donnent un message de case hors plateau. Une case occupée donne un message distinct. Aucun refus ne change le joueur, le compteur ou le plateau.

## Schéma de décomposition de `main`

```text
int main()
├── déclarer Joueur, Coup et Partie
├── initialiser le plateau, les pions, le joueur courant et le compteur
├── saisir les deux noms
└── boucle principale
    ├── afficher la partie et son plateau
    ├── terminer si le plateau est plein
    ├── recommencer la saisie tant que le coup est refusé
    │   ├── lire la ligne et vérifier son format
    │   ├── vérifier les coordonnées
    │   └── vérifier que la case est libre
    ├── poser le pion et compter le coup
    └── passer la main à l’autre joueur
=======
```bash
gcc -std=c23 -Wall -Wextra -Werror -pedantic jeu.c lib/*.c -o jeu -lm
>>>>>>> acf4a0e (Modification de l'ensemble du main version semaine 4, relire avant la remise)
```

Dans VS Code/Linux, ouvrir **`jeu.c` à la racine** et lancer Ctrl+Maj+B : la tâche originale compile le fichier actif et `lib/*.c`. Ouvrir un fichier de bibliothèque pour lancer cette tâche provoquerait une compilation incorrecte. La tâche fournie n’a pas été réécrite.

<<<<<<< HEAD
```text
projet/
├── jeu.c
├── README.md
├── CHANGELOG.md
├── LICENSE
├── LICENSE.*
├── .clang-format
├── .gitignore
├── .vscode/
├── Doxyfile
└── lib/
    ├── exemple.c
    ├── exemple.h
    ├── fonctions.c
    └── fonctions.h
```
=======
Saisir un nom par ligne, sans espace, de 1 à 63 octets. Le premier mot de chaque ligne est retenu ; les lignes blanches sont ignorées par `scanf`. Un nom trop long est refusé et sa fin de ligne est consommée. Le terminateur `\0` occupe le dernier octet disponible ; il est différent du marqueur de fin d’entrée `EOF`. Les caractères accentués UTF-8 peuvent occuper plusieurs octets.

Un coup se saisit sur une seule ligne : `2 3` désigne ligne 2, colonne 3, avec repères de 1 à 3. Les coordonnées hors plateau, les cases occupées et les formats invalides ont des messages distincts. Le joueur recommence sans perdre son tour. Après chaque coup valide, le plateau est réaffiché. Répondre `o` ou `n` au rejeu ; les majuscules sont acceptées. Une autre réponse est refusée.

`./jeu --aide` affiche les instructions et termine avec le code 0. Tout autre argument est refusé sur `stderr` avec le code 1.

## Structures et séparation des responsabilités

`types.h` définit `TAILLE = 3`, `VIDE = ' '`, `CAPACITE_NOM = 64` et `NB_JOUEURS = 2`.

| Structure | Informations |
| --- | --- |
| `struct Joueur` | Nom borné et pion X/O |
| `struct Coup` | Ligne et colonne, coordonnées à partir de 1 |
| `struct Partie` | Plateau, deux joueurs, joueur courant, compteur, état et indice du gagnant |

`enum EtatPartie` distingue `EN_COURS`, `GAGNEE` et `NULLE`. `enum ControleCoup` distingue un coup valide, hors plateau, occupé ou interdit après la fin d’une partie. Les indices de tableau sont calculés seulement après vérification des limites. Les nombres saisis sont plafonnés à `TAILLE + 1`, sans risque de débordement même pour une entrée très longue.

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | Arguments, noms des joueurs, boucle de rejeu et code de retour |
| `lib/types.h` | Informations partagées, constantes et états |
| `lib/plateau.c/.h` | Initialisation, validation, placement, victoire et nul, sans entrée-sortie |
| `lib/saisie.c/.h` | Lecture de `stdin`, noms, coups et réponse au rejeu |
| `lib/affichage.c/.h` | Plateau et résultat sur `stdout` |
| `lib/fonctions.c/.h` | Déroulement d’une partie, coordination des trois autres modules |
| `lib/exemple.c/.h` | Exemple du modèle, compilé par la tâche fournie mais non appelé par le jeu |
| `Doxyfile` | Génération de la documentation dans `html/` |
| `output/` | Entrées rejouables et sorties réelles sur les deux flux |
| `rapport/` | Compte rendu HTML, distinct de la documentation générée |

## Explications des fonctions des bibliothèques

| Signature | Rôle, paramètres et résultat |
| --- | --- |
| `void initialiserPartie(struct Partie *partie)` | Réinitialise le plateau et l’état à travers son adresse ; conserve les noms et associe X/O. Aucun retour. |
| `enum ControleCoup verifierCoup(const struct Partie *partie, struct Coup coup)` | Consulte la partie et le coup sans modification ; renvoie le motif de refus ou `COUP_VALIDE`. |
| `int chercherGagnant(const struct Partie *partie)` | Examine les trois lignes, trois colonnes et deux diagonales ; renvoie l’indice du gagnant ou -1. |
| `enum ControleCoup jouerCoup(struct Partie *partie, struct Coup coup)` | Refuse sans modifier, ou pose le pion, incrémente le compteur, vérifie victoire puis nul, et passe la main si la partie continue. |
| `int demanderNom(struct Joueur *joueur, int numero)` | Remplit le nom du joueur ; le numéro sert au message ; renvoie 1 ou 0 à EOF. |
| `int lireCoup(struct Coup *coup)` | Consomme une ligne, remplit le coup si son format est correct ; renvoie 1, -1 si invalide, 0 à EOF avant la ligne. |
| `int demanderRejouer(void)` | Demande o/n et recommence après une réponse invalide ; renvoie 1 pour oui, 0 pour non, -1 à EOF. |
| `void afficherPartie(const struct Partie *partie)` | Affiche compteur et plateau repéré, sans modifier la partie. Aucun retour. |
| `void afficherResultat(const struct Partie *partie)` | Nomme le gagnant ou annonce le nul d’une partie terminée. Aucun retour. |
| `int jouerPartie(struct Partie *partie)` | Réinitialise puis conduit une partie, en reliant saisie, règles et affichage ; renvoie 1 après un résultat et 0 si interrompue. |
| `void afficheSep(void)` | Exemple fourni : affiche 80 tirets sans paramètre ni retour ; non utilisé dans le jeu. |

Les pointeurs de modification et les paramètres de consultation sont distincts. Les fonctions de logique peuvent être testées sans lecture clavier ni affichage ; elles pourront servir à un adversaire automatique plus tard, sans en implémenter un à cette étape.

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

## Documentation Doxygen

Chaque fonction est documentée avant sa déclaration avec son rôle, ses paramètres et son retour lorsqu’elle en a un. Les définitions reprennent explicitement ces contrats. Les structures, champs et énumérations sont également décrits.

```bash
doxygen Doxyfile
```

Ouvrir ensuite `html/index.html`. Le README est la page d’accueil, le [CHANGELOG](CHANGELOG.md) est aussi intégré. `jeu.c` et tous les fichiers `.c/.h` de `lib/` figurent dans la documentation avec leurs sources. La configuration traite les avertissements comme des erreurs et ne génère pas de PDF/LaTeX.

## Jeux d’essai et flux standard

Le dialogue, les plateaux et les résultats vont sur `stdout`. Les seuls messages sur `stderr` sont les erreurs : saisie invalide, coup refusé, argument invalide ou fin prématurée d’entrée. Une erreur de saisie récupérable ne termine pas le jeu ; une entrée épuisée avant la fin prévue termine immédiatement avec le code 1. Une session complète terminée par `n` renvoie 0.

```bash
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
```

Les [sept scénarios](output/README.md) couvrent les coups limites, la victoire de chacun, le nul, les deux diagonales, une victoire au neuvième coup, plusieurs parties et une entrée interrompue. Les fichiers `.out` et `.err` sont issus de l’exécution réelle. Le bilan des vérifications est dans [output/verification.md](output/verification.md). Même entrée, même sortie ; aucun hasard n’est utilisé. EOF ne relance jamais indéfiniment la saisie.

## Compte rendu HTML et suivi

Le compte rendu HTML (`rapport/index.html`) contient la présentation du jeu et des fonctionnalités, la conception en modules, et un tableau des difficultés et solutions avec responsables. Les membres doivent compléter les observations personnelles au fil des séances ; aucune participation passée n’est inventée. Ce compte rendu est distinct de la documentation Doxygen.

[CHANGELOG.md](CHANGELOG.md) suit les modifications par semaine. Aucun script de génération ni workflow n’est ajouté. Les exécutables locaux et les métadonnées de Git ne font pas partie du rendu. Aucun ZIP n’est créé.
>>>>>>> acf4a0e (Modification de l'ensemble du main version semaine 4, relire avant la remise)

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
