# Changelog

Morpion — G1E. Les mentions de semaine 3 désignent les responsables selon les rôles du README, à valider par chacun. Les mentions historiques des semaines précédentes sont conservées.

## Semaine 3 -- 12/10/26

### Ajouté

- Partie à deux joueurs : saisie des coordonnées, placement des pions et alternance après chaque coup accepté (@ELisa, @Ilan).
- Regroupement du nom et du pion dans `Joueur`, des coordonnées dans `Coup` et de l’état du jeu dans `Partie` (@Ilan, @ELisa).
- Contrôle des formats, des cases hors plateau et des cases occupées ; nouvelle tentative du même joueur après un refus (@ELisa).
- Compteur des coups acceptés et arrêt au plateau plein, sans détection de victoire (@Ilan, @ELisa).

### Modifié

- Toutes les instructions et structures du morpion regroupées dans `main` de `jeu.c`, selon la demande de l’utilisateur (@ELisa).
- README détaillé : cours de référence, notions autorisées, utilisation, structures et schéma de `main` ; écart avec la demande de fonctions de semaine 3 explicité (@Tilio).
- Tâche VS Code limitée à `jeu.c`, avec compilation stricte GCC/Linux (@Mathis).

### Corrigé

- Retrait des saisies avancées et des modules propres au jeu ; utilisation des notions des chapitres 1 à 7 (@ELisa, @Ilan).
- Lecture des nombres plafonnée pour éviter les débordements et arrêt propre à la fin de saisie (@ELisa).
- Retrait des scripts, tests Python, workflows, notes algorithmiques, traces et exécutables hors rendu (@Mathis).
- Vérifications de compilation, des tours, des refus et de la poursuite après un alignement (@Tilio).

## Semaine 2 -- 08/10/26

### Ajouté

- Saisie des noms, initialisation du plateau et affichage repéré (@ELisa, @Ilan).
- Pions de démonstration placés directement dans le code (@ELisa).

### Modifié

- Recentrage du programme sur le jalon de semaine 2 et mise à jour du README (@ELisa, @Ilan, @Tilio, @Mathis).
- Paramètres du modèle et suivi du projet (@Mathis).

## Semaine 1 -- 01/10/26

### Ajouté

- Premières idées de conception et décomposition du morpion (@ELisa, @Ilan).
- Présentation du groupe et répartition des rôles (@Mathis).

### Modifié

- Mise à jour du README et organisation du journal (@Mathis).
