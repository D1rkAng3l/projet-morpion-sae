# Jeux d’essai de semaine 4

Tous les fichiers utilisent les mêmes noms Alice (X) et Bob (O). Un coup est une paire `ligne colonne`, puis `o` ou `n` répond au rejeu. Les sorties `.out` et `.err` ont été produites par le programme, sans fusion des deux flux.

| Entrée | Objectif | Résultat attendu | Code |
| --- | --- | --- | --- |
| `partie-01.in` | Coups limites et victoire X verticale | Alice gagne | 0 |
| `partie-02.in` | Victoire O horizontale | Bob gagne | 0 |
| `partie-03.in` | Match nul | Match nul | 0 |
| `partie-04.in` | Deux victoires X, diagonale puis horizontale ; rejeu et réponse invalide | Alice gagne deux fois | 0 |
| `partie-05.in` | Entrée interrompue en cours de partie | Interruption sur stderr | 1 |
| `partie-06.in` | Victoire X au neuvième coup, prioritaire au nul | Alice gagne | 0 |
| `partie-07.in` | Victoire X sur l’autre diagonale | Alice gagne | 0 |

Rejouer depuis la racine :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
```

`partie-01.err` explique les formats invalides, la case hors plateau et la case occupée. `partie-04.err` refuse une réponse de rejeu. `partie-05.err` annonce une fin prématurée d’entrée ; le programme renvoie 1 et ne demande pas indéfiniment un nouveau coup. Les autres fichiers `.err` sont vides. Les redirections assurent des résultats déterministes ; aucun hasard n’est utilisé.
