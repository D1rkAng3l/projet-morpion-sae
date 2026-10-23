# Changelog

Morpion — G1E. Mathis, Ilan, Elisa et Tilio ont confirmé leurs contributions le 23/10/26, selon la confirmation transmise dans l’échange de suivi. Les mentions historiques des semaines précédentes sont conservées.

## Semaine 4 -- 20/10/26

Les mentions identifient les contributeurs selon le README et le suivi individuel confirmé le 23/10/26.

### Ajouté

- Détection des trois lignes, trois colonnes et deux diagonales gagnantes, annonce du vainqueur ou du nul, priorité à la victoire au neuvième coup (`@Ilan`, `@ELisa`).
- Rejeu avec les mêmes joueurs sur un plateau vide, compteur réinitialisé et X au premier tour (`@ELisa`).
- Modules de logique, saisie, affichage et déroulement ; structures échangées par les fonctions (`@Ilan`, `@ELisa`).
- Documentation de chaque fonction, des paramètres et retours ; Doxyfile, README d’accueil et CHANGELOG intégrés à la documentation HTML (`@Tilio`, `@Mathis`).
- Sept fichiers d’entrée rejouables, sorties stdout/stderr séparées, vérifications des limites, résultats et parties successives (`@Tilio`).
- Compte rendu HTML : présentation, conception, difficultés et solutions, complétées et confirmées le 23/10 (`@Mathis`, `@Tilio`, `@Ilan`, `@ELisa`).

### Modifié

- 23/10 : confirmation des contributions des quatre membres et actualisation du suivi individuel, du README et de la documentation (`@Mathis`, `@Ilan`, `@ELisa`, `@Tilio`).

- 22/10 : module de déroulement renommé `partie.c/.h` ; références et arbre fonctionnel actualisés (`@ELisa`, `@Ilan`, `@Mathis`).
- Lecture des coups décomposée en fonctions simples ; résultats de saisie et de rejeu nommés par énumérations, sans perdre les contrôles de ligne et de débordement (`@ELisa`, `@Ilan`).
- Préconditions documentées, branche inaccessible retirée de la boucle, mode d’emploi complété et documentation HTML régénérée (`@Tilio`).
- Suivi individuel des quatre premières séances structuré, avec contributions et auteurs confirmés le 23/10 ; portée des vérifications historiques clarifiée (`@Mathis`, `@Tilio`).

- Point d’entrée réduit aux arguments, aux noms et à la boucle de rejeu ; abandon du regroupement de tout le jeu dans main (`@ELisa`).
- Schéma du README remplacé par un arbre fonctionnel avec signatures et explication des fonctions de lib/ (`@Ilan`, `@Tilio`, `@Mathis`).
- Relecture des huit chapitres, en particulier modules, flux, arguments et Doxygen du chapitre 8 (`@Ilan`, `@Tilio`,`@ELisa`, `@Mathis`).

### Corrigé

- 22/10 : restauration de `lib/fonctions.c/.h`, nécessaires à `jouerPartie`, après leur suppression (`@ELisa`,`@Mathis`,`@Ilan`, `@Tilio`).
- Après audit du 22/10, suppression de la configuration GDB ajoutée et de sa tâche : les quatre fichiers `.vscode/` sont strictement identiques au ZIP fourni (`@Mathis`).
- Retrait du module d’exemple inutilisé ; README complété avec le rôle de chaque module et la commande de rejeu des essais (`@ELisa`, `@Tilio`).
- Contrats de `jouerCoup` et `main` précisés, documentation et vérifications actualisées (`@Tilio`).

- Configuration VS Code restaurée à l’identique depuis le ZIP, avec la tâche compilant lib/*.c (`@Mathis`).
- Inclusion directe de exemple.c supprimée ; ébauche invalide de fonctions.c remplacée par un module compilable (`@ELisa`).
- Erreurs sur stderr et arrêt immédiat avec code 1 sur entrée incomplète ; code 0 après une session complète (`@ELisa`).
- Date de l’entrée de semaine 3 rétablie au 16/10/26 conformément au retour d’évaluation (`@Mathis`).

## Semaine 3 -- 16/10/26

### Ajouté

- Partie à deux joueurs : saisie des coordonnées, placement des pions et alternance après chaque coup accepté (`@ELisa`, `@Ilan`).
- Regroupement du nom et du pion dans `Joueur`, des coordonnées dans `Coup` et de l’état du jeu dans `Partie` (`@Ilan`, `@ELisa`).
- Contrôle des formats, des cases hors plateau et des cases occupées ; nouvelle tentative du même joueur après un refus (`@ELisa`).
- Compteur des coups acceptés et arrêt au plateau plein, sans détection de victoire (`@Ilan`, `@ELisa`).

### Modifié

- Toutes les instructions et structures du morpion regroupées dans `main` de `jeu.c`, selon la demande de l’utilisateur (`@ELisa`).
- README détaillé : cours de référence, notions autorisées, utilisation, structures et schéma de `main` ; écart avec la demande de fonctions de semaine 3 explicité (`@Tilio`).
- Tâche VS Code limitée à `jeu.c`, avec compilation stricte GCC/Linux (`@Mathis`).

### Corrigé

- Retrait des saisies avancées et des modules propres au jeu ; utilisation des notions des chapitres 1 à 7 (`@ELisa`, `@Ilan`).
- Lecture des nombres plafonnée pour éviter les débordements et arrêt propre à la fin de saisie (`@ELisa`).
- Retrait des scripts, tests Python, workflows, notes algorithmiques, traces et exécutables hors rendu (`@Mathis`).
- Vérifications de compilation, des tours, des refus et de la poursuite après un alignement (`@Tilio`).

## Semaine 2 -- 08/10/26

### Ajouté

- Saisie des noms, initialisation du plateau et affichage repéré (`@ELisa`, `@Ilan`).
- Pions de démonstration placés directement dans le code (`@ELisa`).

### Modifié

- Recentrage du programme sur le jalon de semaine 2 et mise à jour du README (`@ELisa`, `@Ilan`, `@Tilio`, `@Mathis`).
- Paramètres du modèle et suivi du projet (`@Mathis`).

## Semaine 1 -- 01/10/26

### Ajouté

- Premières idées de conception et décomposition du morpion (`@ELisa`, `@Ilan`).
- Présentation du groupe et répartition des rôles (`@Mathis`).

### Modifié

- Mise à jour du README et organisation du journal (`@Mathis`).
