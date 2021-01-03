# FREEDOM  

## Description du projet  

### Concept  

*Ce jeu est grandement inspiré du jeu de plateau Room-25.*

**Des personnages** sont enfermés dans un complexe ayant **25 salles** aux **effets divers et dangereux** représentées par des cases. Le but est d'essayer de sortir le plus rapidement possible sans mourir et arriver ensemble à trouver la Room 25 pour **s’échapper**. Or, la partie commence alors que les personnages se trouve sur la seule case révélée, la salle centrale. Le jeu demande **programmer les actions** des personnages au début de chaque tour, sachant que la perte de ces derniers nous fait perdre la partie. Il existe un **mode solo** (2 personnages) et un **mode multijoueurs** (4 personnages) où les participants peuvent saboter la fuite des autres joueurs.


### Règles et mecaniques de jeu  

#### 1. Tours de jeu
En début de chaque tour les joueurs **programment** leurs **actions** dans l'ordre suivant: 

Dans un premier temps chaque joueur choisi consécutivement ses 2 actions du tour. 

* **Programmation actions du tour:** 

Joueur 1 -> choix action 1 -> choix action 2

Joueur 2 -> choix action 1 -> choix action 2

Joueur 3 -> choix action 1 -> choix action 2

Joueur 4 -> choix action 1 -> choix action 2

* **Deroulenement première partie du tour:**

Joueur 1 -> execution action 1

Joueur 2 -> execution action 1

Joueur 3 -> execution action 1 

Joueur 4 -> execution action 1

* **Deroulement deuxième partie du tour:**

Joueur 1 -> execution action 2

Joueur 2 -> execution action 2

Joueur 3 -> execution action 2

Joueur 4 -> execution action 2

**(Avec joueurs 3 et 4 disponibles seulement dans le mode multijoueurs.)**

#### 2. Actions possibles

* **Regarder**: Action permettant au joueur de regarder n'importe carte cachée du plateau.

* **Controler**: Action permettant de faire glisser les salles en lignes ou en colonnes **à l'exception de la ligne et de la colonne de la salle de départ**.

* **Se Déplacer**: Action permettant aux personnages de bouger d'une salle à une autre. 

* **Pousser**: Action permettant aux personnages de pousser un autre personnage. **(/!\ Seulement disponible dans le mode multijoueurs)**


#### 3. Caractéristiques des Salles

* **Salle 25**: Salle que l'on veut atteindre, condition de reussite

* **Salle de départ**: Salle où tous les personnages débutent la partie.

* **Salle Vortex**: Place le personnage sur la salle de départ.

* **Salle de controle**: Décalez d’un cran toutes les salles de la rangée dans la même direction, comme pour l’action Contrôler, sauf sur les rangées centrales.

* **Salle Tunnel**: Déplace immédiatement votre personnage sur une autre salle tunnel visible de votre choix. S’il n’y en a pas, rien ne se passe.

* **Salle Mobile**: Interverti la position de cette salle et du personnage avec une salle cachée n’importe où sur le plateau. Si toutes les salles sont déjà révélées, rien ne se passe.

* **Salle Mortelle**: Elimine le personnage.

* **Salle Noire**: Tant que le personnage est dans cette salle, l’action Regarder est inutilisable.

* **Salle Froide**: Tant que le personnage est dans cette salle, il ne peut programmer qu'une seule action alors pour le tour.

* **Salle Vision**: Permets au personnage de regarder une salle cachée sur le plateau.

* **Salle Chute**: Lors de la première entrée dans cette pièce rien ne se passe mais lors de la deuxième le sol se dérobe et le joueur fait une chute mortelle.

* **Salle Vide**: Salle n'ayant aucun effet

* **Salle Prison**: Retiens le personnage prisonier pendant 1 tour

* **Salle surprise**: Prend l'effet d'une autre salle aléatoirement

* **Salle copie**: Permet de copier l'effet d'une salle visible au choix

* **Salle virus**: Condamne le joueur à vivre un certain nombre de tour

* **Salle soin**:  Annule l'effet de la salle virus 


## Prérequis  


* SDL2

## Usage  

```
git clone
cd 
make
./main
```

## Suivi  

### Répartition du travail général

Medi: 
* Implémentations des salles
* Gestion du menu de jeu 
* Affichage SDL du menu
      
Marie: 
* Création et gestions du plateau
* Gestions des fichiers (chargements/sauvegardes)
* Implementation d'un struct_world
* Affichage SDL de description de salles en jeu 
       
Chloé: 
* Gestions des personnages et de leur actions 
* Affichage SDL du jeu lancé 
* Interaction avec le joueur (entrées clavier/souris)


### Semaine 1

Medi: Commencement de quelques fonctions salles 

Marie: Affichage d'un plateau sur invite de commande à partir d'un fichier .txt

Chloé: Mise en place des joueurs et leurs actions


### Semaine 2 

Medi: Avancer dans la création de la struct salle et les particularité de ses dernières

Marie: Création d'une fonction SDL affiche_salle et plateau, optimisation du plateau, sa libération mémoire, 

Chloé: Création des joueurs et de leur actions, organisations de l'affichage dans main et fonctions tests


### Semaine 3 

Medi: Finir la création des salles

Marie: Optimisation de la fonction créer plateau pour permettre l'integration un systeme de sauvegarde de fichier plus efficace

Chloé: Gestions de l'interaction joueur/jeu à travers souris/clavier


### Semaine 4 

Medi: Preparation des tests de salles 

Marie: Création d'une branche pour implementer une nouvelle méthode de mise en forme des fichier niveau + adapter création/sauvegarde + verifications 

Chloé: Ajout des boutons cliquable des actions (et possiblement de déplacement) 


### Semaine 5

Medi: Modification des fonctions salles après implementations des tests 

Marie: Factorisation des fcts plateau.c, mise en place de 2 nouveaux plateaux avc demande de niveau, ajouts fcts testPlateau

Chloé: Organisation du main, corrections de bugs liés à l'implementation des boutons cliquable 

### Semaine 6 

Medi: Modification des fonctions salles et mise à jour de leurs tests adéquats 

Marie: Recherche optimisation vérification plateau 

Chloé: Implémentation d'un affichage sur sortie standard pour voir les tours de jeux 

### Semaine 7 

Medi: Corrections du fonctionnement des salles et ajouts de tests en vu de leur implémentation 

Marie: Changement systeme de chargement plateau, complétion vérifications de fichiers fonctionelles, ajout systeme de sauvegarde, début strct_world

Chloé: Ajout de la possibilité de cliquer à nouveau quand clic non valide, affichage des messages à l'écran, complétion du strct_world

### Semaine 8 

Medi: Début de la création du menu de jeu et changement d'implémentation des salles 

Marie: Continuation du struct_world and début d'écriture des fonctions SDL de textes en jeu 

Chloé: Prise en compte de la mort des joueurs, et modifications des tests quant au bon fonctionnement de ces derniers 

### Semaine 9 

Medi: Implémentation de nouvelles salles avec structure de données, avancement et finalisation du menu de jeu 

Marie: Creation du design final du jeu, implémentation de l'affichage de description de salle lors de survol du curseur

Chloé: Création de design final du jeu, implémentation de l'action pousser, prise en compte de 2 modes Solo/multijoueur

### Semaine 10

Medi: Finalisation du menu de jeu

Marie: Finalisation du design du jeu 

Chloé: Support technique











