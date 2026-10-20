# Morpion — SAÉ 1.01 et 1.02

**Groupe : G1E** — Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe projet

| Membre            | Mention | Responsabilité                          |
| ----------------- | ------- | --------------------------------------- |
| Mathis Bretonneau | @Mathis | Coordination, suivi et configuration    |
| Ilan Guiot        | @Ilan   | Conception et algorithmique             |
| Elisa Mayet       | @ELisa  | Développement et intégration            |
| Tilio Dabaji      | @Tilio  | Vérifications, documentation et qualité |

Les mentions de semaine 3 dans le journal indiquent les responsables selon cette répartition. Elles restent à relire et valider par chacun et ne constituent pas une preuve de contribution personnelle.

## Règles et avancement : semaine 3

Deux joueurs posent alternativement X et O sur une grille de 3 × 3. Dans le jeu complet, trois pions identiques alignés horizontalement, verticalement ou en diagonale donnent la victoire. Un plateau plein sans alignement donne un match nul.

Cette version permet de saisir les coups, refuse les cases invalides ou occupées, affiche chaque coup accepté et passe la main au joueur suivant, appelé par son nom. La partie s’arrête après neuf coups acceptés, quand aucune case n’est libre. La détection de victoire est prévue en semaine 4 : un alignement ne termine pas encore la partie, et aucun vainqueur ni match nul n’est annoncé.

La consigne de semaine 3 demande également des fonctions échangeant les structures. Sur instruction de l’utilisateur, le programme conserve tout dans `main` : les regroupements de données sont réalisés, mais cette partie de la décomposition en fonctions n’est pas appliquée.

## Compilation et exécution sous Linux

Utiliser GCC avec le support C23, comme dans la configuration du modèle. Aucune bibliothèque externe n’est nécessaire.

```bash
gcc -std=c23 -Wall -Wextra -Werror -pedantic jeu.c -o jeu
./jeu
```

Dans VS Code, ouvrir le dossier du projet et utiliser **Ctrl+Maj+B** : la tâche compile uniquement `jeu.c`, indépendamment de l’onglet actif. Les fichiers d’exemple de `lib/` ne sont pas compilés.

## Utilisation et saisies

1. Saisir les noms des deux joueurs, un nom par ligne. Le premier reçoit X, le second O.
2. Observer le plateau vide, avec lignes et colonnes numérotées de 1 à 3.
3. Le joueur appelé saisit deux entiers sans signe sur une ligne : `2 3` vise la ligne 2, colonne 3.
4. Une saisie refusée affiche une explication ; le même joueur recommence.
5. Après chaque coup accepté, le plateau et le nombre de coups sont affichés. Après neuf coups, la partie termine.

Un nom est un mot de 1 à 63 octets, conservé dans un tableau de 64 octets. Une ligne vide est ignorée pour les noms ; seul le premier mot d’une ligne est conservé. Un mot trop long est refusé, et sa fin de ligne est consommée avant de recommencer.Il est recommandé de ne pas utiliser d'accents.

Pour les coups, les lignes vides, le texte, les nombres signés ou décimaux, les coordonnées manquantes et les éléments supplémentaires sont refusés. Les valeurs 0 ou supérieures à 3 donnent un message de case hors plateau. Une case occupée donne un message distinct. Aucun refus ne change le joueur, le compteur ou le plateau.

## Représentation des données

| Structure locale à `main` | Champs                                                                                                     |
| ------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `struct Joueur`           | `char nom[CAPACITE_NOM]`, `char pion`                                                                      |
| `struct Coup`             | `int ligne`, `int colonne`                                                                                 |
| `struct Partie`           | `char grille[TAILLE][TAILLE]`, `struct Joueur joueurs[NB_JOUEURS]`, `int joueurCourant`, `int nombreCoups` |

`TAILLE` vaut 3, `VIDE` est un espace, `CAPACITE_NOM` vaut 64 et `NB_JOUEURS` vaut 2. Les coordonnées saisies commencent à 1, les indices internes à 0. Les limites sont vérifiées avant tout accès à la case visée.

`joueurCourant` vaut 0 ou 1 ; `nombreCoups` ne compte que les coups acceptés. Chaque acceptation remplit une case libre. Les nombres lus caractère par caractère sont plafonnés à `TAILLE + 1` : même un très long nombre reste hors plateau sans provoquer de débordement d’entier.

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
```

## Architecture et rendu

projet/
├── jeu.c
├── README.md
├── CHANGELOG.md
├── LICENSE
├── LICENSE.\*
├── .clang-format
├── .gitignore
├── .vscode/
├── Doxyfile
└── lib/
├── exemple.c
├── exemple.h
├── fonctions.c
└── fonctions.h

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
