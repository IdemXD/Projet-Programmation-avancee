/**
	*\file personnages.c
	*\author Chloe Mathias
	*\version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "personnages.h"

persos_t*  creer_persos(int nbPersos)
 {

 	persos_t* persos = (persos_t *) malloc (sizeof(persos_t)*nbPersos); //les personnages du joueur
 	for (int i=0; i<nbPersos;i++){
 		persos[i].coord_x = 2;//On place les personnages dans la salle de départ (au centre)
 		persos[i].coord_y = 2;
 		persos[i].state = 1 ; //les personnages sont vivants
 		persos[i].affecter=1;
 		persos[i].nb_actions = 2;
 		persos[i].actions = (int *) malloc(sizeof(int)*2);
 		persos[i].actions[0] = -1;
 		persos[i].actions[1] = -1;
        persos[i].vie = 10;
 	}
 	return persos ;

 }
int joueurToPersos (int nbJoueurs){
    if (nbJoueurs == 1){//Si il n'y a qu'un joueur, il a le droit a deux personnages
        return 2;
    }
    //Sinon un personnage par joueur
    return nbJoueurs;
}


void liberer_persos(persos_t*  persos,int nbPersos)
 {
 	for (int i=0; i<nbPersos;i++){
 		free(persos[i].actions);
 	}
 	
 	free(persos);
 	persos = NULL;
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
