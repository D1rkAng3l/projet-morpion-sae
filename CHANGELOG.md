# Changelog

Morpion — groupe G1E. Une section par semaine, la plus récente en premier.
Chaque modification indique les membres concernés selon la répartition des rôles du README.
Les dates des titres correspondent à la première entrée conservée de la semaine. Les entrées retracent aussi les versions précédentes ; le README décrit uniquement la version actuelle.

## Semaine 2 -- 08/10/26

### Ajouté

- Test de connexion Tilio (@Tilio).
- Test de connexion Ilan (@Ilan).
- Modification jeu.c, définition de fonctions et de procédures (@Tilio).
- Modules `lib/grille.c/.h` : taille centralisée, plateau initialisé, cases contrôlées et détection des victoires et matchs nuls (@ELisa, @Ilan).
- Modules `lib/saisie.c/.h` : noms bornés, entiers contrôlés, vidage des lignes trop longues et arrêt propre à EOF (@ELisa).
- Anticipation des étapes suivantes : Modules `lib/jeu.c/.h` : deux modes, noms dans les messages, alternance, affichage dans la boucle, résultats et proposition de rejouer (@ELisa).
- Anticipation des étapes suivantes : Module `lib/ia.c/.h` : adversaire automatique aléatoire, tactique et minimax (@Ilan, @ELisa).
- Anticipation des étapes suivantes : Fonctionnalités valorisées : trois difficultés, indices et scores cumulés pendant la session (@ELisa).
- Option `--demo` dans `jeu.c` pour vérifier le plateau avec des pions placés dans le code (@ELisa).
- Anticipation des étapes suivantes : Tests `tests/regles.c`, `tests/comparer.c` et `scripts/verifier.py`, traces réelles et protocole de comparaison dans `output/` (@Tilio).
- Workflow `.github/workflows/verification.yml` pour compilation, tests et documentation sous Linux (@Mathis).
- Anticipation des étapes suivantes : Compte rendu HTML multipage dans `rapport/` : jeu, conception, suivi des contributions, comparaison et bilan (@Mathis, @Tilio).
- Anticipation des étapes suivantes : Scripts de génération du rapport, de contrôle du changelog et de création du ZIP de rendu (@Mathis, @Tilio).

### Modifié

- Retour du programme au jalon de semaine 2 : noms des deux joueurs, plateau initialisé, affichage repéré et pions de démonstration placés dans le code ; schéma et README alignés sur cette version (@ELisa, @Ilan, @Tilio).
- Conservation des propositions initiales du groupe dans lib/algo.txt comme conception pour les étapes suivantes (@Ilan).
- Vérification et workflow limités aux noms, au plateau et à l’affichage, sans génération de documentation ni de rapport HTML (@Tilio, @Mathis).
- Restauration du Doxyfile fourni pour une utilisation ultérieure (@Mathis).

- Clarification du README sur l’algorithme actuel et les propositions initiales conservées dans `lib/algo.txt` ; vérification des exigences disponibles des semaines 1 et 2 et de la documentation C (@Tilio, @Ilan).
- Précision des signatures du parcours de démonstration et des types Grille et Session dans le schéma du README (@Tilio, @Ilan).
- Mise à jour du README dans les sections concernées par les fonctionnalités : plateau, joueurs, modes de jeu, difficultés, indices, scores et rejeu (@Tilio, @Ilan).
- Harmonisation du journal principal avec les mentions des membres et le format hebdomadaire ; retrait des annotations annexes et du renvoi à l’archive supprimée (@Mathis).

- Recentrage du README sur les semaines 1 et 2 : plateau, noms, affichage et démonstration ; distinction des ajouts anticipés et du compte rendu HTML non encore abordé (@Tilio, @Ilan).
- Vérification des exigences documentaires C : règles, utilisation, compilation, représentation, modules et signatures ; fiche détaillée de semaine 1 restant à confirmer (@Tilio, @Ilan).
- Harmonisation des mentions du journal selon les responsabilités du README, conservation des contributions historiques et du gabarit commenté (@Mathis).
- Rétablissement de GCC/Linux comme tâche VS Code par défaut après constat d’une tâche Windows cl.exe par défaut ; configuration fournie restaurée (@Mathis).

- Matrice de conformité et résultats de validation consignés dans `output/conformite.md` ; ZIP de rendu préparé avec sources, configuration, rapport, documentation et traces, sans compilateur portable ni exécutables (@Mathis, @Tilio).
- Modification des fonctions nécessaires à l'implémentation de la grille (@Ilan).
- Modification du CHANGELOG.md (@Mathis).
- Fichier jeu.c initialisation boucle, initialiser grille + afficher grille (@ELisa).
- Ajout et modification des fonctions permettant le comptage des tours et la relation entre le jeu et l'utilisateur à propos de la victoire ou non d'un des deux et lequel des deux doit jouer (@Ilan).
- Modification du fichier .gitignore (@Mathis).
- README aligné sur le programme réalisé, signatures, représentation du plateau, fonctionnalités valorisées, compilation Linux et procédure de tests (@Tilio, @Ilan).
- Configuration Doxygen adaptée au Morpion et génération de la documentation du code dans `html/` (@Tilio).
- CHANGELOG regroupé par semaine, auteurs conservés, gabarit commenté en fin de fichier ; original conservé dans `output/changelog-avant-reorganisation.md` (@Mathis).
- Algorithme `lib/algo.txt` actualisé et fichier `algo` expliqué (@Ilan).

### Corrigé

- Retrait des fonctionnalités ajoutées trop tôt : saisie des coups, victoire, nul, ordinateur, indices, scores et rejeu ; fichiers Doxygen, rapport HTML, sources et outils anticipés conservés hors du projet actif dans `.hors-semaine2/`, exclu de Git (@ELisa, @Mathis).

- Résolution du conflit dans `lib/algo.txt` en conservant les propositions du groupe et le protocole de mesures ; distinction des notes initiales et du fonctionnement actuel (@Ilan, @Mathis).
- Résolution du conflit dans le CHANGELOG, regroupement des entrées de semaine 2 et conservation de la contribution d’Ilan sur les tours et les messages aux joueurs (@Mathis).
- Suppression du ZIP de travail et des fichiers de compilation MSVC ; ajout des exclusions pour éviter de versionner les artefacts de compilation (@Mathis).

- Activation explicite des assertions du test C, vérification des liens HTML et de la configuration Linux, diagnostics Doxygen sans avertissement ; contrôles du changelog automatique sans modifier ses fonctions existantes (@Tilio).
- Fonctions imbriquées dans `main` remplacées par des fonctions de modules réellement appelées (@ELisa, @Ilan).
- Configurations `.vscode/`, `.clang-format` et base `.gitignore` restaurées depuis le ZIP original, avec exclusions des outils de vérification temporaires (@Mathis).
- Présentation du groupe G1E et tableau des rôles clarifiés ; retrait des consignes modèle du README (@Mathis).

## Semaine 1 -- 01/10/26

### Ajouté

- Test de connexion pour Elisa (@ELisa).
- Mise à jour du système de log (@Mathis).
- Test de connexion pour Ilan (@Ilan).
- Ajout du fichier algo.txt dans le dossier lib (@Ilan).
- Initialisation du répertoire html avec index.html et style.css (@Mathis).
- Ajout du squelette du fichier index.html (@Mathis).
- Fichier html, output (@ELisa).

### Modifié

- Test de mise à jour (@Mathis).
- Modification du CHANGELOG.md (@Mathis).
- Mise à jour du CHANGELOG.md (@Mathis).
- Premières réflexions autour des fonctions à utiliser dans le cadre du codage du morpion (@Ilan).
- Premières réflexions autour des fonctions dans le cadre du codage du morpion (@Ilan).
- Mise à jour du README.md (@Mathis).
- Harmonisation du fichier journal (@Mathis).
- Mise à jour du fichier README.md (@Mathis).
- Mise à jour du fichier CHANGELOG.md (@Mathis).
- Schéma de composition (@Mathis).
- Répartition des tâches (@Mathis).
- Schéma de décomposition (@Ilan).
- Ajout des premières idées d'implémentations (@ELisa).

### Corrigé

- Tableau de répartition de l'équipe du README.md ne s'affiche pas correctement (@Mathis).
- Correction de log qui ne remontaient pas (@Mathis).

<!--
Gabarit : ajouter la nouvelle semaine au-dessus des anciennes.
## Semaine N -- JJ/MM/AA

### Ajouté

- Description (@prénom).

### Modifié

- Description (@prénom).

### Corrigé

- Description (@prénom).
-->
