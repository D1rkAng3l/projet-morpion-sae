# Morpion – SAÉ S1.01


**Groupe** : `G[1][E]` -- [Mathis Bretonneau], [Ilan Guiot], [Elisa Mayet], [Tilio Dabaji]


## Équipe projet

Le projet est réalisé par :

| Membre | Rôle |
_________________________________________________________________
| **Mathis Bretonneau** | Chef de projet |
| **Ilan Guiot** | Responsable conception et algorithmique |
| **Elisa Mayet** | Responsable tests, documentation et qualité |
| **Tilio Dabaji** | Responsable des tests, de la documentation et de la qualité | 
_________________________________________________________________

### Mathis 

Chef de projet chargé notamment :

- de la coordination du groupe ;
- de la répartition des tâches ;
- du suivi de l’avancement ;
- de la validation générale du projet ;
- de la coordination des livrables.

### Ilan 

Responsable de la conception et de l’algorithmique, notamment :

- analyse des règles du Morpion ;
- conception des algorithmes ;
- décomposition du programme en fonctions ;
- conception de la gestion des tours ;
- conception de la détection des victoires et des matchs nuls.

### Elisa 

Responsable du développement et de l’intégration, notamment :

- implémentation des fonctions ;
- organisation des modules ;
- intégration des différentes parties du programme ;
- compilation ;
- résolution des erreurs techniques.

### Mathis / Tilio 

Responsable des tests, de la documentation et de la qualité, notamment :

- création des jeux d’essais ;
- exécution des tests ;
- conservation des traces ;
- documentation Doxygen ;
- mise à jour de la documentation du projet.

---


### Fonctionnalités principales

Le programme permet notamment :

- l’initialisation d’une grille de 3 × 3 cases ;
- l’affichage de la grille ;
- la gestion de deux joueurs ;
- l’attribution des symboles `X` et `O` ;
- l’alternance automatique des joueurs ;
- la sélection d’une case ;
- la vérification de la validité d’un coup ;
- le refus d’une case déjà occupée ;
- la détection d’une victoire ;
- la détection d’un match nul ;
- l’affichage du résultat de la partie ;
- la gestion des principales erreurs de saisie.

D’autres fonctionnalités pourront être ajoutées au cours du développement selon les fonctionnalités valorisées retenues dans le cahier des charges.

---

## Description

Ce projet est réalisé dans le cadre de la **SAÉ S1.01 – Implémentation d’un besoin client** du BUT Informatique.

L’objectif est de développer en langage **C** un jeu de **Morpion** permettant à deux joueurs de s’affronter sur une grille de 3 × 3 cases.

Chaque joueur possède un symbole :

- Joueur 1 : `X`
- Joueur 2 : `O`

Les joueurs jouent chacun leur tour en sélectionnant une case disponible de la grille.

Une partie se termine lorsqu’un joueur parvient à aligner trois symboles identiques :

- horizontalement ;
- verticalement ;
- diagonalement.

Si les neuf cases sont occupées sans qu’aucun joueur n’ait réalisé un alignement de trois symboles, la partie se termine par un **match nul**.

## Compilation et exécution

Sous VSCode, la touche `F5` compile le fichier actif (`jeu.c`) avec tous les
modules du dossier `lib/` et lance l'exécutable.

En ligne de commande :

```bash
# TODO: adaptez si votre point d'entrée ou vos options de compilation changent
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```
Options utilisées :

- `-std=c23` : utilisation de la norme C23 ;
- `-Wall` : activation des principaux avertissements du compilateur ;
- `-Werror` : les avertissements sont considérés comme des erreurs ;
- `-o jeu` : création d’un exécutable nommé `jeu` ;
- `-lm` : liaison avec la bibliothèque mathématique.

Le projet ne nécessite actuellement aucune bibliothèque externe supplémentaire.

________________________________________________________________________________________
[Précisez ici toute dépendance ou option particulière propre à votre projet :
bibliothèque externe, arguments de lancement, mode de jeu...]
________________________________________________________________________________________

## Schéma de décomposition

Le programme est décomposé en plusieurs fonctions afin de séparer la gestion de la grille, les interactions avec les joueurs et la vérification des règles du Morpion.

Le schéma suivant représente la structure prévue du programme. Il sera mis à jour au cours du développement si le découpage évolue.

```text
int main(void)
│
├── void initialiserGrille(char grille[3][3])
│
├── void afficherGrille(const char grille[3][3])
│
├── void jouerPartie(char grille[3][3])
│   │
│   ├── int demanderCoup(const char grille[3][3], char joueur)
│   │   │
│   │   └── bool coupValide(const char grille[3][3], int position)
│   │
│   ├── void placerCoup(char grille[3][3], int position, char joueur)
│   │
│   ├── bool verifierVictoire(const char grille[3][3], char joueur)
│   │
│   ├── bool grillePleine(const char grille[3][3])
│   │
│   └── char changerJoueur(char joueur)
│
└── void afficherResultat(char resultat)
```

Cette décomposition est provisoire et pourra être adaptée en fonction de l’évolution du projet.

---

## Organisation du projet

Le projet est organisé afin de séparer le programme principal des différents modules.

```text
.
├── jeu.c
├── lib/
│   ├── grille.c
│   ├── grille.h
│   ├── jeu.c
│   ├── jeu.h
│   ├── saisie.c
│   └── saisie.h
│
├── output/
│
├── html/
│
├── README.md
├── CHANGELOG.md
├── Doxyfile
├── LICENCE
└── LICENCE-CONTENT
```

### Rôle des fichiers

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | Point d’entrée principal de l’application |
| `lib/grille.c` | Gestion de la grille et de son affichage |
| `lib/grille.h` | Déclarations des fonctions liées à la grille |
| `lib/jeu.c` | Gestion des règles et du déroulement d’une partie |
| `lib/jeu.h` | Déclarations des fonctions liées au jeu |
| `lib/saisie.c` | Gestion et validation des saisies utilisateur |
| `lib/saisie.h` | Déclarations des fonctions liées aux saisies |
| `output/` | Traces d’exécution et résultats des jeux d’essais |
| `html/` | Documentation HTML générée par Doxygen |
| `README.md` | Présentation et documentation générale du projet |
| `CHANGELOG.md` | Historique des modifications du projet |
| `Doxyfile` | Configuration de Doxygen |

L’organisation des modules pourra évoluer au cours du développement.



## Documentation

La documentation du code est générée avec [Doxygen](https://www.doxygen.nl/).

La documentation HTML est produite dans le dossier :

```text
html/
```

Pour générer la documentation :

```bash
doxygen Doxyfile
```

Dans le fichier `Doxyfile`, la valeur de `PROJECT_NAME` doit correspondre au nom du projet.

Exemple :

```text
PROJECT_NAME = "Morpion"
```

Les fonctions et modules du projet devront être documentés à l’aide de commentaires compatibles avec Doxygen.

Exemple :

```c
/**
 * @brief Vérifie si un joueur a gagné la partie.
 *
 * @param grille Grille actuelle du Morpion.
 * @param joueur Symbole du joueur à vérifier.
 *
 * @return true si le joueur possède un alignement gagnant,
 *         false sinon.
 */
bool verifierVictoire(const char grille[3][3], char joueur);
```

---

## Jeux d’essais

Les traces d’exécution permettant de vérifier le fonctionnement du programme sont stockées dans le dossier :

```text
output/
```

Les jeux d’essais permettent notamment de vérifier :

- le placement d’un symbole dans une case vide ;
- le refus d’une case déjà occupée ;
- le refus d’une position incorrecte ;
- l’alternance des joueurs ;
- une victoire horizontale ;
- une victoire verticale ;
- une victoire diagonale ;
- un match nul ;
- le comportement du programme après la fin d’une partie.

### Exemple de jeu d’essai

```text
Test : victoire horizontale du joueur X

Entrées :
X → case 1
O → case 4
X → case 2
O → case 5
X → case 3

Résultat attendu :
X | X | X
---------
O | O |
---------
  |   |

Victoire du joueur X.
```

Les traces devront permettre de comparer :

```text
Entrées
   ↓
Résultat attendu
   ↓
Résultat obtenu
   ↓
Validation du test
```

La procédure permettant de rejouer automatiquement ou manuellement les scénarios de test sera précisée au cours du développement.

---

## Qualité du code

Le projet devra respecter plusieurs règles de qualité :

- découpage du programme en fonctions ;
- fonctions ayant une responsabilité clairement définie ;
- noms de variables et de fonctions explicites ;
- limitation de la duplication de code ;
- commentaires lorsque cela est nécessaire ;
- documentation des fonctions avec Doxygen ;
- compilation sans avertissement avec `-Wall -Werror` ;
- tests des principales fonctionnalités.

---

## Journal des changements

L’évolution du projet est documentée dans :

[CHANGELOG.md](./CHANGELOG.md)

Ce fichier permet de conserver une trace des principales modifications réalisées au cours du développement :


- ajout de fonctionnalités ;
```bash
git commit -m "add: fichier" ;
```
- modification de fonctionnalités ;
```bash
git commit -m "mod: fichier" ;
```
- correction d’erreurs ;
```bash
git commit -m "fix: fichier" ;
```
- changement dans l’organisation du code ;
```bash
git commit -m "feat: fichier"
```
- évolution de la documentation.

---

## Licences

Ce projet utilise deux licences libres pour son contenu.

### Contenu écrit

Le contenu écrit est publié sous licence :

[CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

Voir le fichier :

```text
LICENCE-CONTENT
```

### Code source

Les programmes et exemples de code sont publiés sous :

[The Unlicense](https://unlicense.org/)

Voir le fichier :

```text
LICENCE
```