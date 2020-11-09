## Description du projet 

Nom: Freedom

Des personnages sont enfermés dans un complexe ayant 25 salles aux effets divers et dangereux. Le but est d'essayer de sortir le plus rapidement possible sans mourir et arriver ensemble à trouver la Room 25 pour s’échapper.


Jeu

Ce jeu est une adaptation du jeu de plateau Room-25,il se constitue d'un plateau de 25 cases représentant 25 salles toutes cachées au début de la partie à part la salle de départ.C'est un jeu tour par tour ou il faut programmer c'est action au début de chaque tour. Il y a un mode solo ou le joueur contrôle 4 personnages et devra trouver la Room-25 sans perdre de personnage. Dans le mode à plusieurs joueurs des gardiens peuvent se mêler aux personnages et peuvent empêcher la fuite en les sabotants.






Action possible


Regarder

Action permettant au joueur de regarder n'importe carte cachée du plateau



Controler 

Action permettant de faire glisser les salles en lignes ou en colonnes à l'exception de la ligne et de la colonne de la salle de départ.



Se Déplacer

Action permettant aux personnages de bouger d'une salle à une autre. 



Pousser

Action permettant aux personnages de pousser un autre personnage.







Caractéristique des Salles


Salle de départ

Salle où tous les personnages débutent la partie.


Salle Vortex

Place le personnage sur la salle de départ.

Salle de controle 

Fait glisser n’importe quelle rangée du plateau (sauf  les  deux  rangées  centrales)  dans  la direction de votre choix. Décalez d’un cran toutes les salles de la rangée dans la même direction, comme pour l’action Contrôler.

Salle Tunnel

Déplace immédiatement votre personnage sur une autre salle tunnel visible de votre choix. S’il n’y en a pas, rien ne se passe.

Salle Mobile 

Interverti la position de cette salle et du personnage avec une salle cachée n’importe où sur le plateau. Cette dernière salle reste cachée. Si toutes les salles sont déjà révélées, rien ne se passe.

Salle Mortelle

Elimine le joueur.

Salle Noire

Tant que le personnage est dans cette salle,l’action Regarder est inutilisable.

Salle Froide

Tant que le personnage est dans cette salle, il ne peut programmer qu'une seule action alors pour le tour.

Salle Vision 

Permets au personnage de regarder une salle cachée sur le plateau.

Salle Chute

Lors de la première entrée dans cette pièce rien ne se passe mais lors de la deuxième le sol se dérobe et le joueur fait une chute mortelle.

Salle Vide

Salle n'ayant aucun effet


(D'autres salles pourront être ajoutées)


Prérequis


-SDL2












