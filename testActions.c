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
}

void affichage_joueur(persos_t* p){
    for(int i = 0; i < TAILLE_PL; i++)
    {
        for (int j = 0; j < TAILLE_PL; j++){
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




	printf("\n\n##########TEST DEPLACER##########\n");

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

	p[0].coord_x = 2;
	p[0].coord_y = 3;
	choix_dir = 1;
	direction = 'b';
	printf("Avant de se déplacer, état du joueur : %d\n",p[0].state);
	deplacer(pl,&p[0],&direction,&choix_dir);
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