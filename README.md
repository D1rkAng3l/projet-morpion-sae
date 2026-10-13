# Morpion — SAÉ 1.01 et 1.02

**Groupe : G1E** — Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe projet

| Membre | Mention | Responsabilité |
| --- | --- | --- |
| Mathis Bretonneau | @Mathis | Coordination, suivi et configuration |
| Ilan Guiot | @Ilan | Conception et algorithmique |
| Elisa Mayet | @ELisa | Développement et intégration |
| Tilio Dabaji | @Tilio | Vérifications, documentation et qualité |

Les mentions de semaine 3 dans le journal indiquent les responsables selon cette répartition. Elles restent à relire et valider par chacun et ne constituent pas une preuve de contribution personnelle.

## Cadre du cours et règle de développement

La référence autorisée est le [cours R1.01](https://but.lyceum.fr/r101/). Son planning place le chapitre 7 pendant la semaine du 12 octobre 2026 ; le [chapitre 7](https://but.lyceum.fr/r101/c07/) est publié le 12 octobre et aborde les structures. Les numéros des semaines de SAÉ ne sont donc pas les numéros des chapitres.

Toutes les instructions du morpion doivent rester dans **`main` de `jeu.c` à la racine**, y compris les déclarations des structures. Les seuls éléments extérieurs sont l’inclusion de `stdio.h` et les constantes. Aucun module propre au jeu ni fonction auxiliaire n’est utilisé. Lors d’une nouvelle étape, vérifier le chapitre réellement vu avant d’introduire une nouvelle notion ; la présence d’une notion dans un chapitre futur ne l’autorise pas encore.

| Notion utilisée | Ressource du cours |
| --- | --- |
| Types simples, calculs, `printf`, `scanf`, `getchar` | [Chapitre 1](https://but.lyceum.fr/r101/c01/) |
| Conditions, boucles, `break`, `return` | [Chapitre 2](https://but.lyceum.fr/r101/c02/) |
| Tableaux, matrices, indices et parcours | [Chapitre 5](https://but.lyceum.fr/r101/c05/) |
| Noms dans des tableaux de caractères, `%63s`, affichage aligné | [Chapitre 6](https://but.lyceum.fr/r101/c06/) |
| Structures imbriquées, tableaux de structures, accès par `.` | [Chapitre 7](https://but.lyceum.fr/r101/c07/) |

La lecture des coups combine uniquement les opérations élémentaires de ces chapitres. Elle n’utilise ni `fgets`, ni `isspace`, ni `strchr`, ni `memmove`, ni `fflush`, ni conversion avancée.

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

Un nom est un mot de 1 à 63 octets, conservé dans un tableau de 64 octets avec `scanf("%63s", ...)`. Une ligne vide est ignorée pour les noms ; seul le premier mot d’une ligne est conservé. Un mot trop long est refusé, et sa fin de ligne est consommée avant de recommencer. Les accents UTF-8 peuvent occuper plusieurs octets, donc il sera demandé de ne pas utiliser d'accents.

Pour les coups, les lignes vides, le texte, les nombres signés ou décimaux, les coordonnées manquantes et les éléments supplémentaires sont refusés. Les valeurs 0 ou supérieures à 3 donnent un message de case hors plateau. Une case occupée donne un message distinct. Aucun refus ne change le joueur, le compteur ou le plateau.

**Ctrl+D** sur une entrée vide termine proprement la saisie sous Linux. Une dernière ligne complète sans retour à la ligne est traitée avant cette fin de saisie.

## Représentation des données

| Structure locale à `main` | Champs |
| --- | --- |
| `struct Joueur` | `char nom[CAPACITE_NOM]`, `char pion` |
| `struct Coup` | `int ligne`, `int colonne` |
| `struct Partie` | `char grille[TAILLE][TAILLE]`, `struct Joueur joueurs[NB_JOUEURS]`, `int joueurCourant`, `int nombreCoups` |

`TAILLE` vaut 3, `VIDE` est un espace, `CAPACITE_NOM` vaut 64 et `NB_JOUEURS` vaut 2. Les coordonnées saisies commencent à 1, les indices internes à 0. Les limites sont vérifiées avant tout accès à la case visée.

`joueurCourant` vaut 0 ou 1 ; `nombreCoups` ne compte que les coups acceptés. Chaque acceptation remplit une case libre. Les nombres lus caractère par caractère sont plafonnés à `TAILLE + 1` : même un très long nombre reste hors plateau sans provoquer de débordement d’entier.

## Schéma de décomposition de `main`

```text
int main(void)
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

Le projet conserve les fichiers du modèle : `jeu.c`, `README.md`, `CHANGELOG.md`, les deux licences, `.clang-format`, `.gitignore`, `.vscode/`, `Doxyfile` et `lib/exemple.c/.h`. Les exemples sont inchangés et inutilisés. `Doxyfile` est conservé sans générer de documentation HTML.


## Vérification et suivi

Vérifier la compilation sans avertissement, le plateau initial vide, une partie de neuf coups, les pions alternés et le plateau final. Tester les cases occupées ou hors limites, les lignes invalides et les nombres très longs : le même joueur doit rejouer. Tester la fin de saisie pendant les noms et les coups. Un alignement avant le neuvième coup doit laisser la partie continuer.

[CHANGELOG.md](CHANGELOG.md) décrit les changements par semaine. La victoire sera ajoutée à l’étape prévue ; l’IA, le rejeu et les scores restent hors du périmètre actuel.

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
