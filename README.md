# FREEDOM  

## Description du projet  

### Concept  

*Ce jeu est grandement inspiré du jeu de plateau Room-25.*

**Deux personnages** sont enfermés dans un complexe ayant **25 salles** aux effets divers et dangereux représentées par des cases. Le but est d'essayer de sortir le plus rapidement possible sans mourir et arriver ensemble à trouver la Room 25 pour **s’échapper**. Or, la partie commence alors que les personnages se trouve sur la seule case révélée, la salle centrale. Le jeu demande **programmer les actions** des personnages au début de chaque tour, sachant que la perte d'un de ces derniers nous fait perdre la partie. Il existe un **mode solo** et un **mode multijoueurs** où des "gardiens" peuvent se mêler aux personnages et peuvent empêcher la fuite en les sabotants.


### Mécaniques de jeu  

#### 1. Action possible
* **Regarder**: Action permettant au joueur de regarder n'importe carte cachée du plateau

* **Controler**: Action permettant de faire glisser les salles en lignes ou en colonnes à l'exception de la ligne et de la colonne de la salle de départ.

* **Se Déplacer**: Action permettant aux personnages de bouger d'une salle à une autre. 

* **Pousser**: Action permettant aux personnages de pousser un autre personnage.


#### 2. Caractéristique des Salles

* **Salle 25**: Salle que l'on veut atteindre, condition de reussite

* **Salle de départ**: Salle où tous les personnages débutent la partie.

* **Salle Vortex**: Place le personnage sur la salle de départ.

* **Salle de controle**: Décalez d’un cran toutes les salles de la rangée dans la même direction, comme pour l’action Contrôler, sauf sur les rangées centrales.

* **Salle Tunnel**: Déplace immédiatement votre personnage sur une autre salle tunnel visible de votre choix. S’il n’y en a pas, rien ne se passe.

* **Salle Mobile**: Interverti la position de cette salle et du personnage avec une salle cachée n’importe où sur le plateau. Cette dernière salle reste cachée. Si toutes les salles sont déjà révélées, rien ne se passe.

* **Salle Mortelle**: Elimine le joueur.

* **Salle Noire**: Tant que le personnage est dans cette salle,l’action Regarder est inutilisable.

* **Salle Froide**: Tant que le personnage est dans cette salle, il ne peut programmer qu'une seule action alors pour le tour.

* **Salle Vision**: Permets au personnage de regarder une salle cachée sur le plateau.

* **Salle Chute**: Lors de la première entrée dans cette pièce rien ne se passe mais lors de la deuxième le sol se dérobe et le joueur fait une chute mortelle.

* **Salle Vide**: Salle n'ayant aucun effet

*(D'autres salles pourront être ajoutées)*


## Prérequis  


* SDL2

## Usage  

```
git clone
cd 
make .
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














