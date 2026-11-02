# Vérification après le retour d’évaluation — 2 novembre 2026

- Compilation GCC/Linux avec `-std=c23 -Wall -Wextra -Werror -pedantic` : réussie.
- Sept scénarios rejoués deux fois : résultats, sorties et codes reproductibles. Le scénario 05 renvoie 1 ; les autres renvoient 0.
- Le message de format dans `partie-01.err` demande désormais deux chiffres ; les autres sorties de référence sont inchangées.
- Victoire au neuvième coup, victoire de chaque joueur, nul et rejeu conservés.
- EOF testé avant les noms, pendant un coup et avant le choix de rejeu : arrêt avec code 1, sans boucle infinie.
- Noms de 63/64 octets, texte, coordonnées 0/4, éléments supplémentaires et très longue saisie essayés : les refus sont sur stderr et le joueur recommence.
- Les quatre fichiers `.vscode/` sont strictement identiques au ZIP fourni.
- Doxyfile comparé au modèle : les 2 987 lignes et les commentaires sont conservés ; cinq lignes de réglage seulement sont modifiées.
- Documentation générée avec Doxygen ; toutes les fonctions et procédures des fichiers actuels y figurent.

## Reproduire les essais livrés

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
doxygen Doxyfile
```

Remplacer `01` par `02` à `07`. Les descriptions et les codes attendus sont dans `output/README.md`.

## Portée des contrôles

La lecture utilise maintenant scanf, qui ignore les blancs entre les coordonnées ; elle ne prétend plus contrôler un format strict de deux nombres par ligne. Le nettoyage vérifie les caractères supplémentaires après la paire. Chaque coordonnée est limitée à un chiffre, sans conversion manuelle ni plafonnement.

Un contrôle temporaire des règles a aussi été exécuté avec AddressSanitizer et UndefinedBehaviorSanitizer sur les chemins légaux du morpion. Cet outil n’est pas livré ; il ne remplace pas les sept scénarios reproductibles ci-dessus. La détection des fuites est désactivée pour la compatibilité avec l’environnement ; le jeu n’alloue pas de mémoire dynamique.
