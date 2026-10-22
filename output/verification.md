# Vérifications réelles

## Contrôle après corrections — 22/10/2026

- Les quatre fichiers `.vscode/` sont identiques octet par octet au ZIP fourni. Aucun `launch.json` ni tâche de débogage supplémentaire n’est conservé.
- Compilation stricte, sept jeux d’essai et génération Doxygen revérifiés après correction.
- README complété : rôle des modules et commande pour rejouer les entrées avec deux flux séparés.
- Commentaires présents pour les 11 fonctions et procédures ; contrats de placement et code de retour précisés.

## Contrôle initial — 20/10/2026

- Compilation GCC/Linux avec la commande du modèle et avec `-Wextra -pedantic` : réussie sans avertissement.
- Paramètres VS Code et `.clang-format` comparés octet par octet au ZIP fourni : identiques.
- Sept entrées `.in` exécutées deux fois, puis avec l’exécutable local `./jeu` : sorties `.out`, `.err` et codes identiques.
- Essais supplémentaires : arguments, EOF initial ou en cours de partie, ligne finale sans retour, formats invalides, 10 000 chiffres et limites de noms à 63/64 octets : réussis.
- Vérification indépendante des règles par masques de cases : 549 946 positions sur tous les chemins légaux, dont 255 168 parties terminées. Victoires, nuls, alternance, refus sans mutation et réinitialisation avec conservation des noms : réussis.
- Vérification des règles avec AddressSanitizer et UndefinedBehaviorSanitizer : aucun diagnostic. La détection des fuites est désactivée pour la compatibilité avec l’environnement ; le jeu n’alloue pas de mémoire dynamique.
- `doxygen Doxyfile` : réussite sans avertissement ; toutes les fonctions et tous les fichiers sources figurent dans `html/`.
- Liens locaux des pages du compte rendu et de l’accueil Doxygen : cibles présentes.

Les outils de contrôle ponctuels résident dans `/tmp`, hors du rendu ; les sept jeux d’essai livrés sont rejouables avec les commandes de `output/README.md`.
