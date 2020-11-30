/**
	*\file personnages.c
	*\author Chloe Mathias
	*\version 1.0
*/

#include <stdlib.h>
#include "personnages.h"

 persos_t*  creer_persos()
 {

 	persos_t* persos = malloc (sizeof(persos_t)*NB_PERSONNAGES); //les personnages du joueur
 	for (int i=0; i<NB_PERSONNAGES;i++){
 		persos[i].coord_x = 2;//On place les personnages dans la salle de départ (au centre)
 		persos[i].coord_y = 2;
 		persos[i].state = 1 ; //les personnages sont vivants
 		persos[i].nb_actions = 2;
 		persos[i].actions = (int *) malloc(sizeof(int)*2);
 		persos[i].actions[0] = -1;
 		persos[i].actions[1] = -1;
 	}
 	return persos ;

 }


 void liberer_persos(persos_t*  persos)
 {
 	for (int i=0; i<NB_PERSONNAGES;i++){
 		free(persos[i].actions);
 	}
 	free(persos);
 }