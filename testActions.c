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

void affichage_visible(salle_t** pl){
	for (int i = 0;i< TAILLE_PL;i++){
		for (int j = 0;j< TAILLE_PL;j++){
			printf("| %d |",pl[i][j].visible);
		}
		printf("\n");
	}
}

void affichage_utilisable(salle_t** pl){
	for (int i = 0;i< TAILLE_PL;i++){
		for (int j = 0;j< TAILLE_PL;j++){
			printf("| %d |",pl[i][j].state);
		}
		printf("\n");
	}
}

void affichage_joueur(persos_s* p){
	for (int i = 0;i< TAILLE_PL;i++){
		for (int j = 0;j< TAILLE_PL;j++){
			if ((p[0].coord_x == j && p[0].coord_y == i)||(p[1].coord_x == j && p[1].coord_y == i)){
				printf("J");
			}
			else{
				printf("0");
			}
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {

	salle_t ** pl;
	persos_s* p;

	pl = creer_plateau();
	init_salles(pl);
	p = creer_persos();

	affichage_plateau_brut(pl);


	//TEST REGARDER
	printf("\nAvant regarder : ");
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);
	//Test avec une salle normale

	printf("\nAprès regarder : ");
	regarder(pl,0,0);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);

	//Test avec une salle tunnel
	printf("\nAvec un tunnel : ");
	regarder(pl,3,1);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);
	//Avec une seule salle visible
	printf("\nAvec les deux tunnels : ");
	regarder(pl,1,4);
	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);

	//TEST DEPLACER
	

	printf("\nLe joueur n'a pas encore choisit de direction\n");
	int choix_dir = 0;
	char direction = 'n';

	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	deplacer(pl,&p[0],&direction,&choix_dir);

	if (choix_dir){
		printf("Le joueur peut choisir la direction.\n");
	}else{
		printf("Le joueur ne peut pas choisir la direction.\n");
	}
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);



	printf("\nLe joueur choisit la droite\n");
	choix_dir = 1;
	direction = 'd';
	printf("direction = %c\n",direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	deplacer(pl,&p[0],&direction,&choix_dir);
	printf("direction = %c\n",direction);

	if (choix_dir){
		printf("Le joueur peut choisir la direction.\n");
	}else{
		printf("Le joueur ne peut pas choisir la direction.\n");
	}

	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);



	printf("\nLe joueur choisit le haut\n");
	choix_dir = 1;
	direction = 'h';
	printf("direction = %c\n",direction);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	deplacer(pl,&p[0],&direction,&choix_dir);
	printf("direction = %c\n",direction);

	if (choix_dir){
		printf("Le joueur peut choisir la direction.\n");
	}else{
		printf("Le joueur ne peut pas choisir la direction.\n");
	}

	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);

	printf("\n  Visibilité : \n");
	affichage_visible(pl);
	printf("\n  Utilisabilité : \n");
	affichage_utilisable(pl);
	affichage_joueur(p);

	printf("\nLe joueur choisit le bas\n");
	choix_dir = 1;
	direction = 'b';
	deplacer(pl,&p[0],&direction,&choix_dir);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);

	printf("\nLe joueur choisit la gauche\n");
	choix_dir = 1;
	direction = 'g';
	deplacer(pl,&p[0],&direction,&choix_dir);
	printf("Coordonnées du joueur : x = %d et y = %d\n",p[0].coord_x,p[0].coord_y);
	affichage_joueur(p);

	p[0].coord_x = 3;
	p[0].coord_y = 3;
	choix_dir = 1;
	direction = 'b';
	printf("Avant de se déplacer, état du joueur : %d\n",p[0].state);
	deplacer(pl,&p[0],&direction,&choix_dir);
	printf("Après s'être déplacé, état du joueur : %d\n",p[0].state);
	affichage_joueur(p);

	//TEST CONTROLER

	//à faire
	
	free_plateau(pl);
	liberer_persos(p);

	return 0;
}