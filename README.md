# Morpion — SAÉ 1.01 et 1.02

**Groupe** : `G1E` — Mathis Bretonneau, Ilan Guiot, Elisa Mayet, Tilio Dabaji.

## Équipe projet

| Membre | Mention | Rôle |
| --- | --- | --- |
| Mathis Bretonneau | @Mathis | Coordination, suivi et configuration |
| Ilan Guiot | @Ilan | Conception et algorithmique |
| Elisa Mayet | @ELisa | Développement et intégration |
| Tilio Dabaji | @Tilio | Tests, documentation et qualité |

## Sujet et avancement

Le jeu choisi est le morpion : deux joueurs posent alternativement X et O sur une grille de 3 × 3. Un alignement horizontal, vertical ou diagonal gagne. Un plateau plein sans alignement donne un match nul. Ces règles décrivent le jeu prévu ; leur implémentation viendra après la semaine 2.

La version actuelle correspond uniquement au jalon de **semaine 2** : connaître les joueurs, mémoriser et initialiser le plateau, puis vérifier son affichage. Elle ne permet pas encore de jouer une partie.

## Fonctionnalités de semaine 2

### Connaître les joueurs

Le programme demande le nom de chaque joueur et le conserve dans un tableau de caractères de 64 octets. Un nom peut contenir jusqu’à 63 octets. Les noms vides et les saisies trop longues sont refusés ; le reste d’une ligne trop longue est consommé avant une nouvelle demande. X est associé au premier joueur, O au second. Le message « À nom de jouer » identifie le premier joueur. Une fin de saisie termine proprement le programme.

### Mémoriser et initialiser le plateau

`Grille` désigne un tableau `char[TAILLE][TAILLE]`. Chaque case contient `VIDE` (un espace), `X` ou `O`. La taille est définie en un seul endroit, dans `lib/grille.h`. `initialiserGrille` remet toutes les cases à VIDE au lancement. Le même tableau reste en mémoire et sert à tous les affichages de cette exécution.

### Afficher le plateau

La grille est affichée en console avec des cases alignées et des lignes et colonnes numérotées à partir de 1. Le programme affiche d’abord le plateau vide, puis place directement X et O dans le code et réaffiche le tableau pour vérifier que l’affichage suit son état. Il annonce ensuite le joueur dont ce serait le tour. Aucune saisie de coup n’est proposée à ce stade.

## Compilation et exécution sous Linux

Utiliser GCC avec le support de C23. Aucune bibliothèque externe n’est nécessaire.

```bash
gcc -std=c23 -Wall -Wextra -Werror -pedantic jeu.c lib/*.c -o jeu -lm
./jeu
```

Saisir les deux noms, puis observer les deux affichages. Ctrl+D termine la saisie sous Linux. Dans VS Code/Linux, ouvrir `jeu.c` à la racine et utiliser Ctrl+Maj+B pour la tâche GCC. La configuration `.vscode/` et `.clang-format` provient du modèle fourni.

## Schéma de décomposition

Les signatures correspondent aux fonctions actuellement implémentées.

```text
int main(void)
├── bool demanderNom(char *nom, size_t capacite, int numero) — pour chacun des deux joueurs
│   └── int lireLigne(char *texte, size_t capacite)
├── void initialiserGrille(Grille grille)
└── void afficherGrille(const Grille grille) — plateau vide puis avec pions de démonstration
```

## Organisation du projet

| Chemin | Rôle |
| --- | --- |
| `jeu.c` | Lecture des noms et démonstration du plateau |
| `lib/grille.c`, `lib/grille.h` | Représentation, initialisation et affichage |
| `lib/saisie.c`, `lib/saisie.h` | Lecture bornée des noms |
| `lib/exemple.c`, `lib/exemple.h` | Exemple original, non utilisé par la démonstration |
| `lib/algo.txt` | Algorithme actuel et notes de conception du groupe pour la suite |
| `scripts/update_changelog.py` | Mise à jour du journal à partir des commits |
| `scripts/verifier.py`, `tests/test_changelog.py` | Vérifications de la démonstration et du journal |
| `output/` | Traces des vérifications de semaine 2 |
| `Doxyfile` | Configuration du modèle conservée pour une étape ultérieure, sans génération de documentation |

Les propositions initiales du groupe sont conservées dans `lib/algo.txt`. Elles décrivent aussi des fonctionnalités futures et ne doivent pas être confondues avec le programme actuel.

## Vérifications

```bash
python3 scripts/verifier.py --cc gcc
python3 -m unittest discover -s tests -p 'test_*.py'
```

Le premier script compile le programme et vérifie les noms, le refus des lignes trop longues, les noms vides, la fin de saisie, le plateau vide et les pions placés dans le code. Les traces indiquent les entrées, les résultats attendus et ceux obtenus. `output/environnement.json` précise le système et le compilateur réellement utilisés ; une vérification locale Windows ne remplace pas la validation GCC/Linux.

## Journal et rendu

[CHANGELOG.md](CHANGELOG.md) conserve les modifications par semaine, avec les catégories Ajouté, Modifié et Corrigé et les mentions des membres. La dernière entrée décrit le retour au périmètre de semaine 2 ; les entrées précédentes restent historiques.

La capture de semaine 2 fixe le rendu au **vendredi 9 octobre 2026 à 23 h 59** : un ZIP du dossier complet `s101-sae-main`, un seul par groupe, de 50 Mo maximum. La fiche détaillée de semaine 1 n’a pas été fournie ; le choix du jeu, le groupe, les rôles et le schéma sont renseignés conformément aux éléments disponibles.

La saisie des coups est prévue à l’étape suivante. L’adversaire automatique, le rejeu, les scores, les comparaisons, Doxygen et le compte rendu HTML ne sont pas réalisés dans cette version.

Les travaux des étapes ultérieures ont été conservés localement dans `.hors-semaine2/`, exclu de Git. Ils ne sont ni compilés ni utilisés par cette version. Ce dossier ne doit pas être inclus dans le ZIP de semaine 2.

## Licences

Code : [The Unlicense](LICENCE). Contenu écrit : [CC BY-SA 4.0](LICENCE-CONTENT).
