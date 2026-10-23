# Vérifications de semaine 4

## Version après simplification — 22/10/2026

- Compilation GCC/Linux avec `-std=c23 -Wall -Wextra -Werror -pedantic` et l’analyseur GCC : réussite sans diagnostic.
- Les quatre fichiers `.vscode/` sont identiques octet par octet au ZIP fourni ; aucun fichier supplémentaire n’est présent.
- Les sept scénarios livrés ont été rejoués : sorties `.out`, `.err` et codes conformes aux références, y compris après le renommage en `partie.c/.h`.
- La lecture simplifiée a été comparée à celle de la version précédente sur 5 014 lignes : formats corrects, incorrects, longues entrées, blancs et dernière ligne sans retour. Les résultats et coordonnées sont identiques. Ce contrôle ponctuel utilise des outils temporaires et n’est pas inclus dans les fichiers d’essai livrés.
- Les résultats de saisie et de rejeu sont désormais nommés par énumérations ; les refus de coup ne modifient toujours pas la partie.
- Les 13 fonctions et procédures disposent de commentaires de documentation ; les contrats précisent les préconditions des adresses et de l’état de la partie.
- Documentation générée avec `doxygen Doxyfile`, sans avertissement. Le dossier `html/` est suivi par Git et doit être régénéré après modification.

## Vérifications reproductibles avec le rendu

Depuis la racine :

```bash
gcc -std=c23 -Wall -Wextra -Werror -pedantic jeu.c lib/*.c -o jeu -lm
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
```

Rejouer de la même manière les scénarios 02 à 07. Le code de retour attendu et le rôle de chaque scénario sont dans le fichier `output/README.md`. Le scénario 05 doit renvoyer 1 car son entrée s’interrompt ; les six autres renvoient 0. Les sorties de référence sont conservées dans les fichiers `.out` et `.err` livrés.

```bash
doxygen Doxyfile
```

La génération doit réussir et produire `html/index.html`, la page du CHANGELOG et celles des fonctions de `jeu.c` et `lib/`.

## Contrôles historiques, hors protocole livré

Le 20/10, un outil temporaire a parcouru 549 946 positions sur les chemins légaux, dont 255 168 parties terminées, et vérifié les règles avec AddressSanitizer et UndefinedBehaviorSanitizer. La détection des fuites était désactivée pour la compatibilité avec l’environnement. Cette observation est historique : l’outil n’est pas livré, et les sept scénarios ci-dessus ne reproduisent pas à eux seuls cette vérification exhaustive. Elle ne remplace donc pas le protocole reproductible du rendu.
