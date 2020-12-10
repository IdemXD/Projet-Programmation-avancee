/**
	*\file testActions.c
	*\author Chloe Mathias
*/

#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "personnages.h"
#include "plateau.h"
#include "salle.h"

/*void affichage_visible(salle_t** pl){
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++){
			printf("| %d |",pl[i][j].visible);
		}
		printf("\n");
	}
}

void affichage_utilisable(salle_t** pl){
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++){
			printf("| %d |",pl[i][j].state);
		}
		printf("\n");
	}
}*/

int main(int argc, char* argv[]) {

	salle_t ** pl;
	persos_t* p;

	pl = creer_plateau();
	init_salles(pl);
	p = creer_persos();

	affichage_plateau_brut(pl);

	printf("\n\n##########TEST REGARDER##########\n");

	printf("\nAvant regarder : ");
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");

	affichage_utilisable(pl);
	//Test avec une salle normale

	printf("\nAprès regarder en (0,0): ");
	regarder(pl,0,0);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);

	//Test avec une salle tunnel
	printf("\nAvec un tunnel (en (3,1)): ");
	regarder(pl,3,1);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);
	//Avec une seule salle visible
	printf("\nAvec les deux tunnels (en (1,4)): ");
	regarder(pl,1,4);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);



	char direction;
	printf("\n\n##########TEST DEPLACER##########\n");

	printf("\nLe joueur choisit la droite\n");
	direction = 'd';
	printf("direction = %c\n",direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	deplacer(pl,&p[0],&direction);
	printf("direction = %c\n",direction);



	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);



	printf("\nLe joueur choisit le haut\n");
	direction = 'h';
	printf("direction = %c\n",direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	deplacer(pl,&p[0],&direction);
	printf("direction = %c\n",direction);


	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);
	affichage_joueur(p);

	printf("\nLe joueur choisit le bas\n");
	direction = 'b';
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	deplacer(pl,&p[0],&direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);

	printf("\nLe joueur choisit la gauche\n");
	direction = 'g';
	deplacer(pl,&p[0],&direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);

	p[0].coord_x = 2;
	p[0].coord_y = 3;
	direction = 'b';
	printf("Avant de se déplacer, état du joueur : %d et position : (%d,%d)\n",p[0].state,p[0].coord_x,p[0].coord_y);
	deplacer(pl,&p[0],&direction);
	printf("Après s'être déplacé, état du joueur : %d\n",p[0].state);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);




	printf("\n\n##########TEST CONTROLER##########\n");
	//Le joueur se trouve à la case (3,1)
	//Déplacement vers la droite
	p[0].coord_x = 4;
	p[0].coord_y = 1;
	direction = 'd';
	printf("\nDéplacement droite (sur ligne 1)\n");
	printf("Coordonnées du joueur avant : x = %d et y = %d\n",p[0].coord_y,p[0].coord_y);
	affichage_joueur(p);
	affichage_plateau_brut(pl);
	controler(pl,&direction,p[0].coord_y,p);
	printf("\nAprès contrôler\n");
	printf("Coordonnées du joueur après: x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);
	affichage_plateau_brut(pl);


	//Vérification avec déplacement vertical
	p[0].coord_x = 0;
	p[0].coord_y = 0;
	direction = 'b';
	printf("\n\nDéplacement bas (sur colonne 0)\n");
	printf("Coordonnées du joueur avant : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);
	affichage_plateau_brut(pl);
	controler(pl,&direction,p[0].coord_x,p);
	printf("\nAprès contrôler\n");
	affichage_plateau_brut(pl);
	printf("Coordonnées du joueur après: x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);


	//Vérification qu'il n'y a pas de modification car on ne peut pas déplacer la colonne 2 et la ligne 2
	p[0].coord_x = 2;
	p[0].coord_y = 1;
	direction = 'h';
	printf("Déplacement vers le haut (sur ligne 2)\n");
	affichage_plateau_brut(pl);
	printf("Coordonnées du joueur avant : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);
	controler(pl,&direction,p[0].coord_x,p);
	printf("\nAprès contrôler\n");

	affichage_plateau_brut(pl);
	printf("Coordonnées du joueur après: x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);

	p[0].coord_x = 1;
	p[0].coord_y = 0;
	p[1].coord_x = 0;
	p[1].coord_y = 1;
	direction = 'd';
	printf("Déplacement vers la droite (sur ligne 0)\n");
	affichage_plateau_brut(pl);
	printf("Affichage des joueurs\n");
	affichage_joueur(p);
	controler(pl,&direction,p[0].coord_y,p);
	printf("\nAprès contrôler\n");

	affichage_plateau_brut(pl);
	printf("Affichage des joueurs\n");
	affichage_joueur(p);


	p[0].coord_x = 3;
	p[0].coord_y = 0;
	p[1].coord_x = 3;
	p[1].coord_y = 2;
	direction = 'h';
	printf("Déplacement vers le haut (sur colonne 3)\n");
	affichage_plateau_brut(pl);
	printf("Affichage des joueurs\n");
	affichage_joueur(p);
	controler(pl,&direction,p[0].coord_x,p);
	printf("\nAprès contrôler\n");

	affichage_plateau_brut(pl);
	printf("Affichage des joueurs\n");
	affichage_joueur(p);




	free_plateau(pl);
	liberer_persos(p);

	return 0;
}
